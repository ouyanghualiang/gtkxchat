#include "Provider.h"
#include <android/log.h>
#include <android_native_app_glue.h>
#include <jni.h>
#include <log_print.h>
JNIEnv* jniEnv;

JavaVM* g_javaVM;
JNIEnv *env;
JavaVM *jvm;
JavaVMInitArgs vm_args;
extern jclass myClass;
jclass TestProvider;
jobject mTestProvider;
jmethodID getTime;
jmethodID sayHello;
jobject activityInstance;

int GetProviderInstance(jclass obj_class);

/**
 * 初始化 类、对象、方法
 */
int InitProvider() {

	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "InitProvider Begin  1" );

	if(jniEnv == NULL) {
		__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "jniEnv is NULL" );
		//g_javaVM = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
		//jniEnv = JNU_GetEnv();
		return 0;
	}
	
	if(TestProvider == NULL) {
		TestProvider = (*jniEnv)->GetObjectClass(jniEnv,activityInstance);
		//TestProvider = myClass;
		if(TestProvider == NULL){
			__android_log_print(10,"ouyang","-----%s---%d---%s--------",__FILE__,__LINE__,"myClass is NULL");
			return -9;
		}
		__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "InitProvider Begin  2 ok" );
	}

	if (mTestProvider == NULL) {
		if (GetProviderInstance(TestProvider) != 1) {
			(*jniEnv)->DeleteLocalRef(jniEnv, TestProvider);
			return -1;
		}
		__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "InitProvider Begin  3 ok" );
	}

	if (getTime == NULL) {
		__android_log_print(10,"ouyang","-----%s---%d--------",__FILE__,__LINE__);
		getTime = (*jniEnv)->GetStaticFieldID(jniEnv, TestProvider, "gtThh","()Ljava/lang/String;");
		__android_log_print(10,"ouyang","-----%s---%d--------",__FILE__,__LINE__);
		if (getTime == NULL) {
			(*jniEnv)->DeleteLocalRef(jniEnv, TestProvider);
			(*jniEnv)->DeleteLocalRef(jniEnv, mTestProvider);
			return -2;
		}
		__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "InitProvider Begin  4 ok" );
	}

	if (sayHello == NULL) {
		sayHello = (*jniEnv)->GetMethodID(jniEnv, TestProvider, "sayHello","(Ljava/lang/String;)V");
		if (sayHello == NULL) {
			(*jniEnv)->DeleteLocalRef(jniEnv, TestProvider);
			(*jniEnv)->DeleteLocalRef(jniEnv, mTestProvider);
			(*jniEnv)->DeleteLocalRef(jniEnv, getTime);
			return -3;
		}
		__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "InitProvider Begin  5 ok" );
	}

	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "InitProvider Begin  6" );
	return 1;

}

int GetProviderInstance(jclass obj_class) {

	if(obj_class == NULL) {
		return 0;
	}

	jmethodID construction_id = (*jniEnv)->GetMethodID(jniEnv, obj_class,
			"<init>", "()V");

	if (construction_id == 0) {
		return -1;
	}

	mTestProvider = (*jniEnv)->NewObject(jniEnv, obj_class,
			construction_id);

	if (mTestProvider == NULL) {
		return -2;
	}

	return 1;
}

/**
 * 获取时间 ---- 调用 Java 方法
 */
char * GetTime() {
	if(TestProvider == NULL || getTime == NULL) {
		int result = InitProvider();
		__android_log_print(10,"ouyang","-----%s---%d---:%d-----",__FILE__,__LINE__,result);
		if (result != 1) {
			return "result != 1";
		}
	}
	__android_log_print(10,"ouyang","-----%s---%d--------",__FILE__,__LINE__);
	jstring jstr = NULL;
	char* cstr = NULL;
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "GetTime Begin" );
	jstr = (*jniEnv)->CallStaticObjectMethod(jniEnv, TestProvider, getTime);
	cstr = (char*) (*jniEnv)->GetStringUTFChars(jniEnv,jstr, 0);
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "Success Get Time from Java , Value = %s",cstr );
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "GetTime End" );

	(*jniEnv)->ReleaseStringUTFChars(jniEnv, jstr, cstr);
	(*jniEnv)->DeleteLocalRef(jniEnv, jstr);
	return cstr;
}

/**
 * SayHello ---- 调用 Java 方法
 */
void SayHello() {
	if(TestProvider == NULL || mTestProvider == NULL || sayHello == NULL) {
		int result = InitProvider() ;
		if(result != 1) {
			return;
		}
	}

	jstring jstrMSG = NULL;
	jstrMSG =(*jniEnv)->NewStringUTF(jniEnv, "Hi,I'm From C");
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "SayHello Begin" );
	(*jniEnv)->CallVoidMethod(jniEnv, mTestProvider, sayHello,jstrMSG);
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "SayHello End" );

	(*jniEnv)->DeleteLocalRef(jniEnv, jstrMSG);
}

 void getWebPicture(struct android_app* app)
{
    /*
    activityInstance = app->activity->clazz;
    jvm = app->activity->vm;
    env = NULL;
    (*jvm)->GetEnv(jvm, (void **) &jniEnv, JNI_VERSION_1_6);
    if ((*jvm)->AttachCurrentThread(jvm, &jniEnv, NULL) < 0)
    {
     LOGE("callback_handler: failed to attach current thread");
     return;
    }
    jclass clazz = (*jniEnv)->GetObjectClass(jniEnv,activityInstance);
    if (!clazz) {
    LOGE("------callback_handler: failed to get WebPicCls class reference------");	
    (*jvm)->DetachCurrentThread(app->activity->vm);
    return;
    }
    if (getTime == NULL) {
		getTime = (*jniEnv)->GetStaticFieldID(jniEnv, TestProvider, "gtThh","()Ljava/lang/String;");
		if (getTime == NULL) {
			(*jniEnv)->DeleteLocalRef(jniEnv, TestProvider);
			(*jniEnv)->DeleteLocalRef(jniEnv, mTestProvider);
			return -2;
		}
		__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "InitProvider Begin  4 ok" );
	}
    
    myClass = clazz;
	//jniEnv = env;
	*/
	
	jobject activityInstance = app->activity->clazz;
    JavaVM* jvm = app->activity->vm;
    JNIEnv *env = NULL;

    (*jvm)->GetEnv(jvm, (void **) &env, JNI_VERSION_1_6);

    if ((*jvm)->AttachCurrentThread(jvm, &env, NULL) < 0)
    {
     LOGE("callback_handler: failed to attach current thread");
     return;
    }

    jclass clazz = (*env)->GetObjectClass(env, activityInstance);
    if (!clazz) {
    LOGE("callback_handler: failed to get WebPicCls class reference");

    (*jvm)->DetachCurrentThread(app->activity->vm);
    return;
    }

    jmethodID methodID = (*env)->GetMethodID(env, clazz, "LoadWebSite", "(Ljava/lang/String;)V");
    if (!methodID) {
    LOGE("callback_handler: failed to get LoadWebSite method ID");
    (*jvm)->DetachCurrentThread(app->activity->vm);
    return;
    }

    jstring url= (*env)->NewStringUTF(env, "http://198.168.1.104");

    (*env)->CallVoidMethod(env, activityInstance, methodID, url);

    (*env)->ReleaseStringUTFChars(env,url,(*env)->GetStringUTFChars(env, url, 0));

    (*jvm)->DetachCurrentThread(jvm);
}
















