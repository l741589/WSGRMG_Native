pushd %~dp0
::set NDK_PROJECT_PATH=%cd%
::set NDK_TOOLCHAIN_VERSION=4.8
set nkdbuild="%NDK_ROOT%\ndk-build.cmd"
set package=com.bigzhao.jianrmagicbox
::set sdcard=/sdcard
set sdcard=/data/local/tmp
call %nkdbuild% NDK_DEBUG=0
if not %errorlevel%==0 goto :EOF

::adb shell pm clear com.bigzhao.jianrmagicbox
::adb shell rm /data/data/com.bigzhao.jianrmagicbox/lib/libMagicBox.so
::adb push obj\local\armeabi\libMagicBox.so /data/data/%package%/lib/libMagicBox.so
::adb shell rm /sdcard/test/libMagicBox.so
adb push obj\local\armeabi\libMagicBox.so %sdcard%/test/libMagicBox.so
call bc copy :: %sdcard%/test/libMagicBox.so::files:MagicBox/module/libMagicBox.so
::adb shell am force-stop com.bigzhao.jianrmagicbox
::adb shell am broadcast -a com.bigzhao.jianrmagicbox.action.RECEIVER -e action copy -e args_str %sdcard%/test/libMagicBox.so,files:MagicBox/module/libMagicBox.so
::adb push D:\android-ndk-r10e\sources\cxx-stl\gnu-libstdc++\4.9\libs\armeabi\libgnustl_shared.so /data/data/com.bigzhao.cbtcrack/lib/libgnustl_shared.so
::adb push obj\local\armeabi\libgnustl_shared.so /data/data/com.bigzhao.cbtcrack/libgnustl_shared.so
::adb shell rm /data/data/com.bigzhao.cbtcrack/lib/libgnustl_shared.so
::adb shell rm /data/data/com.bigzhao.cbtcrack/libgnustl_shared.so

::adb shell am start %package%/com.bigzhao.jianrmagicbox.LoaderActivity
popd