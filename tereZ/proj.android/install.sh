#!/usr/bin/env sh
adb install -r bin/tereZ-debug.apk
adb shell am start -n org.oxygine.tereZ/org.oxygine.tereZ.MainActivity
