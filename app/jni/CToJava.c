#include <string.h>
#include <android/log.h>
#include <jni.h>
#include "Provider.h"

JNIEnv* jniEnv = NULL;

/**
 *  Java 中 声明的native getTime 方法的实现
 */
void Java_com_duicky_MainActivity_getTime(JNIEnv* env, jobject thiz)
{

	if(jniEnv == NULL) {
		jniEnv = env;
	}

	GetTime();
}

/**
 *  Java 中 声明的native sayHello 方法的实现
 */
void Java_com_duicky_MainActivity_sayHello(JNIEnv* env, jobject thiz)
{
	if (jniEnv == NULL) {
		jniEnv = env;
	}

	SayHello();
}
