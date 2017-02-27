GTKAndroid
==========

编译：
	cd app/
	ndk-build
	./../gradlew assembleDebug
	adb install -r build/outputs/apk/app-debug.apk
log日志打印
	adb logcat -c 		清除
	adb logcat			打印
	adb logcat | ndk-stack -sym ./obj/local/armeabi			错误日志分析
