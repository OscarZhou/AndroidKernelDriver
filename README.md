# AndroidKernelDriver

### Files description:

	1.goldfish_sensor.c    //driver file
	
	2.test.cpp		//test program
	
	3.screenshot.png	//test result
	
	4.test			//excutable file of test
	
	5.read.txt		//the use instruction



### Drive Part:

1 ~/Documents/goldfish          make -j4

2 ~/Android/Sdk/emulator	./emulator64-arm -avd Nexus4 -kernel /home/oscar/Documents/goldfish/arch/arm/boot/zImage

3 ~/Android/Sdk/platform-tools	./adb shell

				cat /dev/goldfish_sensor  //open the sensor
				
				dmesg	//check log


### Test Part:

complie test :    arm-none-linux-gnueabi-gcc -static test.cpp -o test1

in directory Anroid/Sdk/platform-tools:   ./adb push ~/Downloads/test1 /dev

~/Android/Sdk/platform-tools   ./adb shell 

				cd /dev 
				
				./test1


