#ifndef APPLICATION_WATCH_H
#define APPLICATION_WATCH_H

#include <libkern/c++/OSString.h>
#include <IOKit/IOLocks.h>
#include <sys/kauth.h>
#include <sys/vnode.h>
#include <libkern/crypto/sha1.h>

#include "simpleBase.h"

class __attribute__((visibility("hidden"))) Application: public SimpleBase
{
public:
	//static Application *applications;
	//static IOLock *lock;
	//static IOLock *lockRoutine;
	//static IOThread thread;
	//static SInt32 closing;
	//static SInt32 countProcessesToCheck;
	
	//static kauth_listener_t processListener;

public:
	//static bool InitGlobal();
	//static void FreeGlobal();
	//static void CheckApplicationsIsLiveRoutine(void *arg);
	//static Application* GetApplication(); 
	//static Application* AddApplication(vfs_context_t vfsContext, vnode_t vnode);
	//static Application* AddApplication(kauth_cred_t cred, vnode_t vnode, const char *filePath);
//	static int CallbackProcessListener
//					(
//					   kauth_cred_t    credential,
//					   void *          idata,
//					   kauth_action_t  action,
//					   uintptr_t       arg0,
//					   uintptr_t       arg1,
//					   uintptr_t       arg2,
//					   uintptr_t       arg3
//					 );
//	static int CallbackVnodeListener
//					(
//					 kauth_cred_t    credential,
//					 void *          idata,
//					 kauth_action_t  action,
//					 uintptr_t       arg0,
//					 uintptr_t       arg1,
//					 uintptr_t       arg2,
//					 uintptr_t       arg3
//					 );
	
public:
	pid_t pid;
	pid_t p_pid;
	uid_t uid;
	gid_t gid;
	OSString *processName;
	OSString *filePath;
	
	Application *prev;
	Application *next;

	virtual void Free()
	{
		::IOLog("application deleted pid: %d\n", this->pid);
		
		if(filePath)
			filePath->release();
		
		if(processName)
			processName->release();
		
		SimpleBase::Free();
	}
	
//	Application* removeFromChain()
//	{
//		if(prev)
//			prev->next = next;
//		
//		if(this == applications)
//			applications = next;
//		
//		if(next)
//			next->prev = prev;
//		
//		prev = next = NULL;
//		return this;
//	}
	
};


class __attribute__((visibility("hidden"))) Applications
{
public:
	Application *applications;
	IOLock *lock;
	IOLock *lockRoutine;
	IOThread thread;
	SInt32 closing;
	SInt32 countProcessesToCheck;
	
	kauth_listener_t processListener;
	
public:
	bool Init();
	void Free();
	Application* GetApplication(); 
	//Application* AddApplication(vfs_context_t vfsContext, vnode_t vnode);
	Application* AddApplication(kauth_cred_t cred, vnode_t vnode, const char *filePath);

	static void CheckApplicationsIsLiveRoutine(void *arg);
	static int CallbackProcessListener
	(
	 kauth_cred_t    credential,
	 void *          idata,
	 kauth_action_t  action,
	 uintptr_t       arg0,
	 uintptr_t       arg1,
	 uintptr_t       arg2,
	 uintptr_t       arg3
	 );
//	static int CallbackVnodeListener
//	(
//	 kauth_cred_t    credential,
//	 void *          idata,
//	 kauth_action_t  action,
//	 uintptr_t       arg0,
//	 uintptr_t       arg1,
//	 uintptr_t       arg2,
//	 uintptr_t       arg3
//	 );
	
public:
	
	Application* RemoveFromChain(Application* application)
	{
		if(application->prev)
			application->prev->next = application->next;
		
		if(application == applications)
			applications = application->next;
		
		if(application->next)
			application->next->prev = application->prev;
		
		application->prev = application->next = NULL;
		return application;
	}
	
};

#endif 