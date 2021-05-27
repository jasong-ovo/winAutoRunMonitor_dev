
#include "gjcTask.h"
#include "verify.h"


using namespace std;

int get_task_in_subfolder(ITaskService * pService, wstring dir) {
	ITaskFolder *pRootFolder = NULL;
	HRESULT hr;
	//hr = pService->GetFolder(_bstr_t(L"\\"), &pRootFolder);
	//wcout << dir.c_str()<<endl;
	hr = pService->GetFolder(_bstr_t(dir.c_str()), &pRootFolder);
	//hr = pService->GetFolder(_bstr_t(L""), &pRootFolder);
	//pService还要用不能realease掉
	//pService->Release();
	if (FAILED(hr))
	{
		printf("Cannot get Root Folder pointer: %x\n", hr);
		CoUninitialize();
		return 1;
	}
	//  -------------------------------------------------------
	//  Get the registered tasks in the folder.
	IRegisteredTaskCollection* pTaskCollection = NULL;
	hr = pRootFolder->GetTasks(NULL, &pTaskCollection);

	pRootFolder->Release();
	if (FAILED(hr))
	{
		printf("Cannot get the registered tasks.: %x", hr);
		CoUninitialize();
		return 1;
	}

	LONG numTasks = 0;
	hr = pTaskCollection->get_Count(&numTasks);

	if (numTasks == 0)
	{
		printf("\nNo Tasks are currently running\n");
		pTaskCollection->Release();
		CoUninitialize();
		return 1;
	}


	TASK_STATE taskState;

	for (LONG i = 0; i < numTasks; i++)
	{
		IRegisteredTask* pRegisteredTask = NULL;
		hr = pTaskCollection->get_Item(_variant_t(i + 1), &pRegisteredTask);

		if (SUCCEEDED(hr))
		{
			BSTR taskName = NULL;
			BSTR path = NULL;
			wstring info;
			hr = pRegisteredTask->get_Name(&taskName);
			if (SUCCEEDED(hr))
			{
				BSTR imagePath = NULL;
				hr = pRegisteredTask->get_State(&taskState);
				if (SUCCEEDED(hr))
					if (taskState < 2) { 
						pRegisteredTask->Release();
						pTaskCollection->Release();
						return 1; 
					}
					else {
						ITaskDefinition* taskDefination = NULL;
						hr = pRegisteredTask->get_Definition(&taskDefination);
						if (FAILED(hr))
							continue;

						IActionCollection* taskActions = NULL;
						hr = taskDefination->get_Actions(&taskActions);
						if (FAILED(hr))
							continue;
						taskDefination->Release();

						IAction* action = NULL;
						hr = taskActions->get_Item(1, &action);
						if (FAILED(hr))
							continue;
						taskActions->Release();

						IExecAction* execAction = NULL;
						hr = action->QueryInterface(IID_IExecAction, (void**)&execAction);
						if (FAILED(hr))
							continue;
						action->Release();

						hr = execAction->get_Path(&imagePath);
						VerifyEmbeddedSignature(imagePath, &info);

					}
				else
					printf("\n\tCannot get the registered task state: %x", hr);
				printf("  TASK: %ws\n", taskName);
				printf("  INCLUDE PATH: %ws\n", imagePath);
				printf("  SIGN AND VERIFY: %ws\n", info.c_str());
				wcout << endl;
				SysFreeString(taskName);
			}
			else
			{
				printf("\nCannot get the registered task name: %x", hr);
			}
			pRegisteredTask->Release();
		}
		else
		{
			printf("\nCannot get the registered task item at index=%d: %x", i + 1, hr);
		}
	}

	pTaskCollection->Release();
}




void get_live_task(ITaskService * pService, wstring taskDir, wstring fileName) {
	// list current folder
	get_task_in_subfolder(pService, taskDir);

	//loop the sub folder
	HANDLE hFind;
	WIN32_FIND_DATA fileInfo;
	WCHAR * fileNames;
	WCHAR * fileImagePath;

	// 遍历64位库里的目录名
	//fileName = L"C:\\Windows\\Sysnative\\Tasks\\*.*";

	//打开文件夹
	hFind = FindFirstFile(fileName.c_str(), &fileInfo);
	if (hFind == INVALID_HANDLE_VALUE) {
		printf("open first file error!\n");
		printf("code:%ld\n", GetLastError());
		return;
	}

	//遍历文件当前目录下的文件，如果是task文件就验证是否是启动的
	//如果是目录继续进去遍历
	while (FindNextFile(hFind, &fileInfo)) {
		if (!wcscmp(fileInfo.cFileName, L"..") || !wcscmp(fileInfo.cFileName, L".")) continue;
		if (fileInfo.dwFileAttributes == 0x10) {
			if (!wcscmp(L"Microsoft", fileInfo.cFileName)) continue;
			// combine path
			wstring subDir, subFileName;
			subDir = taskDir;
			subFileName = fileName;
			subFileName.erase(subFileName.find(L"*.*"));
			subFileName.append(fileInfo.cFileName);
			subFileName.append(L"\\*.*");
			subDir.append(L"\\");
			subDir.append(fileInfo.cFileName);
			//wcout << subFileName.c_str() << endl;
			//wcout << subDir.c_str() << endl << endl;

			get_live_task(pService, subDir, subFileName);
			/*printf("%ws\n", fileInfo.cFileName);*/
		}
	}

	FindClose(hFind);

}

void get_task_info()
{
	//  ------------------------------------------------------
	//  Initialize COM.
	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		printf("\nCoInitializeEx failed: %x", hr);
		return;
	}

	//  Set general COM security levels.
	hr = CoInitializeSecurity(
		NULL,
		-1,
		NULL,
		NULL,
		RPC_C_AUTHN_LEVEL_PKT_PRIVACY,
		RPC_C_IMP_LEVEL_IMPERSONATE,
		NULL,
		0,
		NULL);

	if (FAILED(hr))
	{
		printf("\nCoInitializeSecurity failed: %x", hr);
		CoUninitialize();
		return;
	}

	//  ------------------------------------------------------
	//  Create an instance of the Task Service. 
	ITaskService *pService = NULL;
	hr = CoCreateInstance(CLSID_TaskScheduler,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_ITaskService,
		(void**)&pService);
	if (FAILED(hr))
	{
		printf("Failed to CoCreate an instance of the TaskService class: %x", hr);
		CoUninitialize();
		return;
	}

	//  Connect to the task service.
	hr = pService->Connect(_variant_t(), _variant_t(),
		_variant_t(), _variant_t());
	if (FAILED(hr))
	{
		printf("ITaskService::Connect failed: %x", hr);
		pService->Release();
		CoUninitialize();
		return;
	}

	//  ------------------------------------------------------
	//  Get the pointer to the root task folder.
	// loop all the folder here
	// 输出根目录下的task
	//L"C:\\Windows\\Sysnative\\Tasks\\*";
	wstring fileName, taskDir;
	fileName = L"C:\\Windows\\Sysnative\\Tasks\\*.*";
	taskDir = L"";
	get_live_task(pService, taskDir, fileName);


	CoUninitialize();
}