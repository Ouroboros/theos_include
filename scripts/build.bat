: '
@echo off
cd/d "%~dp0"

bash --init-file "%~nx0"
copy build\packages\*.deb .
timeout /t 3
goto:eof

'

export THEOS=/mnt/d/Dev/iOS/theos
export PATH=$THEOS/bin:$THEOS/toolchain/linux/iphone/bin:$PATH
make clean
make DEBUG=0 -j package install
exit
