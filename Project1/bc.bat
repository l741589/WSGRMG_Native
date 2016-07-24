if "%1"=="" exit /B
if "%2"=="" exit /B
if "%3"=="" exit /B
adb shell am broadcast -a com.bigzhao.jianrmagicbox.action.RECEIVER -e action %~1 -e args_sp %~2 -e args_str %~3