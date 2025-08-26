#include <windows.h>
#include <stdio.h>
#include <intrin.h>

#define ART_NEURO_00 "\t\033[38;2;208;168;136m#***#**=***********#\033[38;2;156;106;71m+.\033[38;2;208;168;136m#**#####*#*\033[38;2;156;106;71m+\033[38;2;208;168;136m#*************%#\033[38;2;133;73;40m. ...\n" \
                     "\t\033[38;2;208;168;136m*=*#*==**#%%#%%%#*#%\033[38;2;156;106;71m -\033[38;2;208;168;136m#**%%%%%#%+\033[38;2;156;106;71m=*\033[38;2;208;168;136m%***#%%%%##+*###\033[38;2;133;73;40m: .. \n" \
                     "\t\033[38;2;208;168;136m=+##*.+##%%##*%*++#\033[38;2;156;106;71m+.+\033[38;2;208;168;136m#**%####*#*\033[38;2;156;106;71m--\033[38;2;208;168;136m%%+**#%%%%##+***#-\033[38;2;133;73;40m . \n" \
                     "\t\033[38;2;208;168;136m=**#=:####****+++*+\033[38;2;156;106;71m=*+\033[38;2;208;168;136m***#*****#*\033[38;2;156;106;71m--+\033[38;2;208;168;136m#*=*+*+**##*+#**#=\033[38;2;133;73;40m. \n" 
#define ART_NEURO_04 "\t\033[38;2;208;168;136m***#==#**+****#\033[38;2;156;106;71m+=\033[38;2;208;168;136m+\033[38;2;208;168;136m-%@\033[38;2;156;106;71m=*\033[38;2;208;168;136m*+********\033[38;2;156;106;71m:%=+\033[38;2;208;168;136m#++#**+++***+*+**:\t\t\033[38;2;208;168;136m"
#define ART_NEURO_05 "\t\033[38;2;208;168;136m****+*****#*+#\033[38;2;156;106;71m=-\033[38;2;255;238;229m=-%@@\033[38;2;156;106;71m++\033[38;2;208;168;136m*+******#*\033[38;2;156;106;71m:\033[38;2;255;238;229m@@-*#\033[38;2;208;168;136m++##****+****+* \t\t\033[38;2;156;106;71m-----------------------\n"
#define ART_NEURO_06 "\t\033[38;2;208;168;136m*****+****#+*\033[38;2;156;106;71m==\033[38;2;255;238;229m+*@@@@\033[38;2;156;106;71m*==\033[38;2;208;168;136m*+#****##\033[38;2;156;106;71m:\033[38;2;255;238;229m%@@-+#\033[38;2;208;168;136m*+##*##%#*##++-\t\tOS: \033[38;2;255;238;229m"
#define ART_NEURO_07 "\t\033[38;2;208;168;136m+******##%*\033[38;2;156;106;71m===\033[38;2;255;238;229m=*@@@@@@\033[38;2;156;106;71m+:\033[38;2;208;168;136m++****+**\033[38;2;156;106;71m-#\033[38;2;255;238;229m@@@**\033[38;2;156;106;71m#--#\033[38;2;208;168;136m*+#@=:-++#=\t\tKernel: \033[38;2;255;238;229m"
#define ART_NEURO_08 "\t\033[38;2;208;168;136m*****+#*#\033[38;2;156;106;71m*.  :\033[38;2;255;238;229m.. .-+@@\033[38;2;156;106;71m#--\033[38;2;208;168;136m++##**+*\033[38;2;156;106;71m:*\033[38;2;255;238;229m@@@# .=. \033[38;2;156;106;71m:  :\033[38;2;208;168;136m%#-=.+#\t\tUptime: \033[38;2;255;238;229m"
#define ART_NEURO_09 "\t\033[38;2;208;168;136m+****##\033[38;2;156;106;71m+. \033[38;2;255;238;229m-@+.@@-++=@@\033[38;2;156;106;71m+-=-\033[38;2;208;168;136m*##**\033[38;2;156;106;71m+--\033[38;2;255;238;229m@@\033[38;2;182;242;237m+  @%+@\033[38;2;255;238;229m#=\033[38;2;156;106;71m  :\033[38;2;208;168;136m=*%+-=\t\tShell: \033[38;2;255;238;229m"
#define ART_NEURO_10 "\t\033[38;2;208;168;136m***##\033[38;2;156;106;71m*-:.\033[38;2;208;168;136m:\033[38;2;255;238;229m@@:\033[38;2;182;242;237m  -+  %\033[38;2;255;238;229m@@@@\033[38;2;156;106;71m=+=:\033[38;2;208;168;136m*##*\033[38;2;156;106;71m++*\033[38;2;255;238;229m=\033[38;2;182;242;237m@.  =: =\033[38;2;255;238;229m@@\033[38;2;156;106;71m\033[38;2;156;106;71m+.-\033[38;2;208;168;136m-==+=:\t\tRoot: \033[38;2;255;238;229m"
#define ART_NEURO_11 "\t\033[38;2;208;168;136m*#*=\033[38;2;156;106;71m-:.\033[38;2;208;168;136m-\033[38;2;156;106;71m-\033[38;2;255;238;229m%@@\033[38;2;182;242;237m    .   \033[38;2;255;238;229m@@@@@\033[38;2;156;106;71m+#\033[38;2;255;238;229m*\033[38;2;156;106;71m:=\033[38;2;208;168;136m*#\033[38;2;156;106;71m+-\033[38;2;255;238;229m@#\033[38;2;182;242;237m+  :-   @\033[38;2;255;238;229m@@=\033[38;2;156;106;71m:\033[38;2;208;168;136m-+****\t\tCurrent: \033[38;2;255;238;229m"
#define ART_NEURO_12 "\t\033[38;2;208;168;136m=\033[38;2;156;106;71m--\033[38;2;208;168;136m-=--\033[38;2;156;106;71m=+\033[38;2;255;238;229m%@\033[38;2;182;242;237m*  +@@*: #\033[38;2;255;238;229m@@@@@\033[38;2;156;106;71m#%\033[38;2;255;238;229m@\033[38;2;156;106;71m+-+\033[38;2;208;168;136m*\033[38;2;156;106;71m-+\033[38;2;255;238;229m@@\033[38;2;182;242;237m.=%@#- +\033[38;2;255;238;229m@@%\033[38;2;156;106;71m:\033[38;2;208;168;136m=***+*\t\tResolution: \033[38;2;255;238;229m"
#define ART_NEURO_13 "\t\033[38;2;208;168;136m+**###*\033[38;2;156;106;71m=-\033[38;2;255;238;229m@@@\033[38;2;182;242;237m+@@%%@#*@\033[38;2;255;238;229m@%@@@@\033[38;2;156;106;71m%\033[38;2;255;238;229m%@@\033[38;2;156;106;71m#++\033[38;2;208;168;136m\033[38;2;156;106;71m-*\033[38;2;255;238;229m@@\033[38;2;182;242;237m*%%@@#%\033[38;2;255;238;229m@@@\033[38;2;156;106;71m-\033[38;2;208;168;136m##****\t\tRefresh: \033[38;2;255;238;229m"
#define ART_NEURO_14 "\t\033[38;2;208;168;136m#****##\033[38;2;156;106;71m*:\033[38;2;255;238;229m#@@@\033[38;2;182;242;237m@@%%%%\033[38;2;255;238;229m%@%@@@@@@@@@@@\033[38;2;156;106;71m%#\033[38;2;255;238;229m=*%@%\033[38;2;182;242;237m%#%@\033[38;2;255;238;229m@@@@\033[38;2;156;106;71m-\033[38;2;208;168;136m+#**+*\t\tMemory: \033[38;2;255;238;229m"
#define ART_NEURO_15 "\t\033[38;2;208;168;136m+#*****\033[38;2;156;106;71m*.\033[38;2;255;238;229m*@@@@\033[38;2;247;202;198m%%%@@@@@\033[38;2;255;238;229m%@%@%@%@%%@@@@%%%@%\033[38;2;247;202;198m@%@%%\033[38;2;255;238;229m@@\033[38;2;156;106;71m-\033[38;2;208;168;136m=#****\t\tPageFile: \033[38;2;255;238;229m"
#define ART_NEURO_16 "\t\033[38;2;208;168;136m=+*****#\033[38;2;156;106;71m.\033[38;2;255;238;229m:@%%\033[38;2;247;202;198m#%%%%%%%%\033[38;2;255;238;229m@%@%@%@@@@@%@@@@@\033[38;2;247;202;198m%%%%###%\033[38;2;255;238;229m@\033[38;2;156;106;71m:\033[38;2;208;168;136m=#***+\t\tVirtual: \033[38;2;255;238;229m"
#define ART_NEURO_17 "\t\033[38;2;208;168;136m++=+*#*#\033[38;2;156;106;71m+ \033[38;2;255;238;229m@@%\033[38;2;247;202;198m####%%%%%%\033[38;2;255;238;229m@%@@@%@@@%@%@%@\033[38;2;247;202;198m%@%%###%%\033[38;2;255;238;229m@\033[38;2;156;106;71m:\033[38;2;208;168;136m*****+\t\tDisk: \033[38;2;255;238;229m"
#define ART_NEURO_18 "\t\033[38;2;208;168;136m**+==+#*#\033[38;2;156;106;71m=+\033[38;2;255;238;229m@@%\033[38;2;247;202;198m%%%%%%%%\033[38;2;255;238;229m@%@%@%@@@\033[38;2;144;98;69m*\033[38;2;255;238;229m@@@%@@@%\033[38;2;247;202;198m@%%%%%@\033[38;2;255;238;229m#\033[38;2;156;106;71m=\033[38;2;208;168;136m*#++=+\t\tCPU: \033[38;2;255;238;229m"
#define ART_NEURO_19 "\t\033[38;2;156;106;71m+\033[38;2;208;168;136m+*#+-=++=\033[38;2;156;106;71m-*\033[38;2;255;238;229m@@@@@@@@@@%@%@%@@#\033[38;2;144;98;69m*+*\033[38;2;255;238;229m@@@@@%@@@@@@@@\033[38;2;156;106;71m+-\033[38;2;208;168;136m==-++=\t\tGPU: \033[38;2;255;238;229m"
#define ART_NEURO_20 "\t\033[38;2;156;106;71m-+\033[38;2;208;168;136m++#+=++= \033[38;2;156;106;71m:+\033[38;2;255;238;229m#@@@@@@@@@%@@@%@@@@@@@@@%@%@@@@@@\033[38;2;156;106;71m*-:\033[38;2;208;168;136m*++*+-\n" \
                     "\t\033[38;2;156;106;71m -+\033[38;2;208;168;136m=++==+#+.\033[38;2;156;106;71m -=++**\033[38;2;255;238;229m%%@%@%@%@%@@@@@%@%@%@@@%##\033[38;2;156;106;71m=  \033[38;2;208;168;136m**===+:\t\t\033[40m   \033[41m   \033[42m   \033[43m   \033[44m   \033[45m   \033[46m   \033[47m   \033[0m\n" \
                     "\t\033[38;2;208;168;136m:\033[38;2;156;106;71m.-+\033[38;2;208;168;136m=--+==**.\033[38;2;156;106;71m.\033[38;2;255;238;229m@@%%@@@@@@@%@%@%@%@%@@@@@@@@@@\033[38;2;156;106;71m+  =\033[38;2;208;168;136m*=+:+-+\t\t\033[100m   \033[101m   \033[102m   \033[103m   \033[104m   \033[105m   \033[106m   \033[107m   \033[0m\n" \
                     "\t\033[38;2;208;168;136m:-\033[38;2;156;106;71m:-+\033[38;2;208;168;136m+--=++++=\033[38;2;156;106;71m=#\033[38;2;255;238;229m@@@@@@@@@@%@%@%@%@@@@@@@@\033[38;2;156;106;71m*=. -\033[38;2;208;168;136m+*+=:+=-*\n" \
                     "\t\033[38;2;208;168;136m:-=\033[38;2;156;106;71m.:=\033[38;2;208;168;136m++-.-====:\033[38;2;156;106;71m--:\033[38;2;255;238;229m:*%%%@@@@@@@@@@@@%\033[38;2;156;106;71m*+-. ...\033[38;2;208;168;136m-+-..----=\n" \
                     "\t\033[38;2;208;168;136m:-=\033[38;2;156;106;71m  :=\033[38;2;208;168;136m--=-==++==\033[38;2;156;106;71m==-\033[38;2;242;189;180m#%#####%%%%%\033[38;2;156;106;71m*+--::-=:--- :\033[38;2;208;168;136m+=.:.+*+*\033[0m\n"

#define ART_EVIL_00 "\t\033[38;2;149;107;100m#***#**=***********#\033[38;2;108;68;61m+.\033[38;2;149;107;100m#**#####*#*\033[38;2;108;68;61m+\033[38;2;149;107;100m#*************%#\033[38;2;133;73;40m. ...\n" \
                    "\t\033[38;2;149;107;100m*=*#*==**#%%#%%%#*#%\033[38;2;108;68;61m -\033[38;2;149;107;100m#**%%%%%#%+\033[38;2;108;68;61m=*\033[38;2;149;107;100m%***#%%%%##+*###\033[38;2;133;73;40m: ..\n" \
                    "\t\033[38;2;149;107;100m=+##*.+##%%##*%*++#\033[38;2;108;68;61m+.+\033[38;2;149;107;100m#**%####*#*\033[38;2;108;68;61m--\033[38;2;149;107;100m%%+**#%%%%##+***#-\033[38;2;133;73;40m .\n" \
                    "\t\033[38;2;149;107;100m=**#=:####****+++*+\033[38;2;108;68;61m=*+\033[38;2;149;107;100m***#*****#*\033[38;2;108;68;61m--+\033[38;2;149;107;100m#*=*+*+**##*+#**#=\033[38;2;133;73;40m.\n"
#define ART_EVIL_04 "\t\033[38;2;149;107;100m***#==#**+****#\033[38;2;108;68;61m+=\033[38;2;149;107;100m+\033[38;2;149;107;100m-%@\033[38;2;108;68;61m=*\033[38;2;149;107;100m*+********\033[38;2;108;68;61m:%=+\033[38;2;149;107;100m#++#**+++***+*+**:\t\t\033[38;2;149;107;100m"
#define ART_EVIL_05 "\t\033[38;2;149;107;100m****+*****#*+#\033[38;2;108;68;61m=-\033[38;2;254;243;236m=-%@@\033[38;2;108;68;61m++\033[38;2;149;107;100m*+******#*\033[38;2;108;68;61m:\033[38;2;254;243;236m@@-*#\033[38;2;149;107;100m++##****+****+* \t\t\033[38;2;108;68;61m-----------------------\n"
#define ART_EVIL_06 "\t\033[38;2;149;107;100m*****+****#+*\033[38;2;108;68;61m==\033[38;2;254;243;236m+*@@@@\033[38;2;108;68;61m*==\033[38;2;149;107;100m*+#****##\033[38;2;108;68;61m:\033[38;2;254;243;236m%@@-+#\033[38;2;149;107;100m*+##*##%#*##++-\t\tOS: \033[38;2;255;238;229m"
#define ART_EVIL_07 "\t\033[38;2;149;107;100m+******##%*\033[38;2;108;68;61m===\033[38;2;254;243;236m=*@@@@@@\033[38;2;108;68;61m+:\033[38;2;149;107;100m++****+**\033[38;2;108;68;61m-#\033[38;2;254;243;236m@@@**\033[38;2;108;68;61m#--#\033[38;2;149;107;100m*+#@=:-++#=\t\tKernel: \033[38;2;255;238;229m"
#define ART_EVIL_08 "\t\033[38;2;149;107;100m*****+#*#\033[38;2;108;68;61m*.  :\033[38;2;254;243;236m.. .-+@@\033[38;2;108;68;61m#--\033[38;2;149;107;100m++##**+*\033[38;2;108;68;61m:*\033[38;2;254;243;236m@@@# .=. \033[38;2;108;68;61m:  :\033[38;2;149;107;100m%#-=.+#\t\tUptime: \033[38;2;255;238;229m"
#define ART_EVIL_09 "\t\033[38;2;149;107;100m+****##\033[38;2;108;68;61m+. \033[38;2;254;243;236m-@+.@@-++=@@\033[38;2;108;68;61m+-=-\033[38;2;149;107;100m*##**\033[38;2;108;68;61m+--\033[38;2;254;243;236m@@\033[38;2;176;25;64m+  @%+@\033[38;2;254;243;236m#=\033[38;2;108;68;61m  :\033[38;2;149;107;100m=*%+-=\t\tShell: \033[38;2;255;238;229m"
#define ART_EVIL_10 "\t\033[38;2;149;107;100m***##\033[38;2;108;68;61m*-:.\033[38;2;149;107;100m:\033[38;2;254;243;236m@@:\033[38;2;176;25;64m  -+  %\033[38;2;254;243;236m@@@@\033[38;2;108;68;61m=+=:\033[38;2;149;107;100m*##*\033[38;2;108;68;61m++*\033[38;2;254;243;236m=\033[38;2;176;25;64m@.  =: =\033[38;2;254;243;236m@@\033[38;2;108;68;61m\033[38;2;108;68;61m+.-\033[38;2;149;107;100m-==+=:\t\tRoot: \033[38;2;255;238;229m"
#define ART_EVIL_11 "\t\033[38;2;149;107;100m*#*=\033[38;2;108;68;61m-:.\033[38;2;149;107;100m-\033[38;2;108;68;61m-\033[38;2;254;243;236m%@@\033[38;2;176;25;64m    .   \033[38;2;254;243;236m@@@@@\033[38;2;108;68;61m+#\033[38;2;254;243;236m*\033[38;2;108;68;61m:=\033[38;2;149;107;100m*#\033[38;2;108;68;61m+-\033[38;2;254;243;236m@#\033[38;2;176;25;64m+  :-   @\033[38;2;254;243;236m@@=\033[38;2;108;68;61m:\033[38;2;149;107;100m-+****\t\tCurrent: \033[38;2;255;238;229m"
#define ART_EVIL_12 "\t\033[38;2;149;107;100m=\033[38;2;108;68;61m--\033[38;2;149;107;100m-=--\033[38;2;108;68;61m=+\033[38;2;254;243;236m%@\033[38;2;176;25;64m*  +@@*: #\033[38;2;254;243;236m@@@@@\033[38;2;108;68;61m#%\033[38;2;254;243;236m@\033[38;2;108;68;61m+-+\033[38;2;149;107;100m*\033[38;2;108;68;61m-+\033[38;2;254;243;236m@@\033[38;2;176;25;64m.=%@#- +\033[38;2;254;243;236m@@%\033[38;2;108;68;61m:\033[38;2;149;107;100m=***+*\t\tResolution: \033[38;2;255;238;229m"
#define ART_EVIL_13 "\t\033[38;2;149;107;100m+**###*\033[38;2;108;68;61m=-\033[38;2;254;243;236m@@@\033[38;2;176;25;64m+@@%%@#*@\033[38;2;254;243;236m@%@@@@\033[38;2;108;68;61m%\033[38;2;254;243;236m%@@\033[38;2;108;68;61m#++\033[38;2;149;107;100m\033[38;2;108;68;61m-*\033[38;2;254;243;236m@@\033[38;2;176;25;64m*%%@@#%\033[38;2;254;243;236m@@@\033[38;2;108;68;61m-\033[38;2;149;107;100m##****\t\tRefresh: \033[38;2;255;238;229m"
#define ART_EVIL_14 "\t\033[38;2;149;107;100m#****##\033[38;2;108;68;61m*:\033[38;2;254;243;236m#@@@\033[38;2;176;25;64m@@%%%%\033[38;2;254;243;236m%@%@@@@@@@@@@@\033[38;2;108;68;61m%#\033[38;2;254;243;236m=*%@%\033[38;2;176;25;64m%#%@\033[38;2;254;243;236m@@@@\033[38;2;108;68;61m-\033[38;2;149;107;100m+#**+*\t\tMemory: \033[38;2;255;238;229m"
#define ART_EVIL_15 "\t\033[38;2;149;107;100m+#*****\033[38;2;108;68;61m*.\033[38;2;254;243;236m*@@@@\033[38;2;247;202;198m%%%@@@@@\033[38;2;254;243;236m%@%@%@%@%%@@@@%%%@%\033[38;2;247;202;198m@%@%%\033[38;2;254;243;236m@@\033[38;2;108;68;61m-\033[38;2;149;107;100m=#****\t\tPageFile: \033[38;2;255;238;229m"
#define ART_EVIL_16 "\t\033[38;2;149;107;100m=+*****#\033[38;2;108;68;61m.\033[38;2;254;243;236m:@%%\033[38;2;247;202;198m#%%%%%%%%\033[38;2;254;243;236m@%@%@%@@@@@%@@@@@\033[38;2;247;202;198m%%%%###%\033[38;2;254;243;236m@\033[38;2;108;68;61m:\033[38;2;149;107;100m=#***+\t\tVirtual: \033[38;2;255;238;229m"
#define ART_EVIL_17 "\t\033[38;2;149;107;100m++=+*#*#\033[38;2;108;68;61m+ \033[38;2;254;243;236m@@%\033[38;2;247;202;198m####%%%%%%\033[38;2;254;243;236m@%@@@%@@@%@%@%@\033[38;2;247;202;198m%@%%###%%\033[38;2;254;243;236m@\033[38;2;108;68;61m:\033[38;2;149;107;100m*****+\t\tDisk: \033[38;2;255;238;229m"
#define ART_EVIL_18 "\t\033[38;2;149;107;100m**+==+#*#\033[38;2;108;68;61m=+\033[38;2;254;243;236m@@%\033[38;2;247;202;198m%%%%%%%%\033[38;2;254;243;236m@%@%@%@@@\033[38;2;144;98;69m*\033[38;2;254;243;236m@@@%@@@%\033[38;2;247;202;198m@%%%%%@\033[38;2;254;243;236m#\033[38;2;108;68;61m=\033[38;2;149;107;100m*#++=+\t\tCPU: \033[38;2;255;238;229m"
#define ART_EVIL_19 "\t\033[38;2;108;68;61m+\033[38;2;149;107;100m+*#+-=++=\033[38;2;108;68;61m-*\033[38;2;254;243;236m@@@@@@@@@@%@%@%@@#\033[38;2;144;98;69m*+*\033[38;2;254;243;236m@@@@@%@@@@@@@@\033[38;2;108;68;61m+-\033[38;2;149;107;100m==-++=\t\tGPU: \033[38;2;255;238;229m"
#define ART_EVIL_20 "\t\033[38;2;108;68;61m-+\033[38;2;149;107;100m++#+=++= \033[38;2;108;68;61m:+\033[38;2;254;243;236m#@@@@@@@@@%@@@%@@@@@@@@@%@%@@@@@@\033[38;2;108;68;61m*-:\033[38;2;149;107;100m*++*+-\n" \
                    "\t\033[38;2;108;68;61m -+\033[38;2;149;107;100m=++==+#+.\033[38;2;108;68;61m -=++**\033[38;2;254;243;236m%%@%@%@%@%@@@@@%@%@%@@@%##\033[38;2;108;68;61m=  \033[38;2;149;107;100m**===+:\t\t\033[40m   \033[41m   \033[42m   \033[43m   \033[44m   \033[45m   \033[46m   \033[47m   \033[0m\n" \
                    "\t\033[38;2;149;107;100m:\033[38;2;108;68;61m.-+\033[38;2;149;107;100m=--+==**.\033[38;2;108;68;61m.\033[38;2;254;243;236m@@%%@@@@@@@%@%@%@%@%@@@@@@@@@@\033[38;2;108;68;61m+  =\033[38;2;149;107;100m*=+:+-+\t\t\033[100m   \033[101m   \033[102m   \033[103m   \033[104m   \033[105m   \033[106m   \033[107m   \033[0m\n" \
                    "\t\033[38;2;149;107;100m:-\033[38;2;108;68;61m:-+\033[38;2;149;107;100m+--=++++=\033[38;2;108;68;61m=#\033[38;2;254;243;236m@@@@@@@@@@%@%@%@%@@@@@@@@\033[38;2;108;68;61m*=. -\033[38;2;149;107;100m+*+=:+=-*\n" \
                    "\t\033[38;2;149;107;100m:-=\033[38;2;108;68;61m.:=\033[38;2;149;107;100m++-.-====:\033[38;2;108;68;61m--:\033[38;2;254;243;236m:*%%%@@@@@@@@@@@@%\033[38;2;108;68;61m*+-. ...\033[38;2;149;107;100m-+-..----=\n" \
                    "\t\033[38;2;149;107;100m:-=\033[38;2;108;68;61m  :=\033[38;2;149;107;100m--=-==++==\033[38;2;108;68;61m==-\033[38;2;242;189;180m#%#####%%%%%\033[38;2;108;68;61m*+--::-=:--- :\033[38;2;149;107;100m+=.:.+*+*\033[0m\n"

#define ART_WIN_01 "\t\033[38;2;138;200;11m                                               . \n" \
                   "\t\033[38;2;138;200;11m                                   ::=+*#%@@@@@@+\n"
#define ART_WIN_03 "\t\033[38;2;138;200;11m                     .-  -%%@@@@@@@@@@@@@@\033[38;2;103;149;8m@@@@\033[38;2;138;200;11m@@=\t\t"
#define ART_WIN_04 "\t\033[38;2;138;200;11m       ::-=+*#%@@@@@@@@= %@@\033[38;2;103;149;8m@@@@@@@@@@@@@@@@@@\033[38;2;138;200;11m@@-\t\t\033[38;2;103;149;8m-----------------------\n"
#define ART_WIN_05 "\t\033[38;2;138;200;11m      #@@@@@@@@@@\033[38;2;103;149;8m@@@@\033[38;2;138;200;11m@@: *@@\033[38;2;103;149;8m@@@@@@@@@@@@@@@@@@\033[38;2;138;200;11m@@-\t\tOS: \033[38;2;255;238;229m"
#define ART_WIN_06 "\t\033[38;2;138;200;11m      *@@\033[38;2;103;149;8m@@@@@@@@@@@@\033[38;2;138;200;11m@@: *@@\033[38;2;103;149;8m@@@@@@@@@@@@@@@@@@\033[38;2;138;200;11m@@:\t\tKernel: \033[38;2;255;238;229m"
#define ART_WIN_07 "\t\033[38;2;138;200;11m      +@@\033[38;2;103;149;8m@@@@@@@@@@@@\033[38;2;138;200;11m@@: +@@\033[38;2;103;149;8m@@@@@@@@@@@@@@@@@@\033[38;2;138;200;11m@@-\t\tUptime: \033[38;2;255;238;229m"
#define ART_WIN_08 "\t\033[38;2;138;200;11m      +@@\033[38;2;103;149;8m@@@@@@@@@@@@\033[38;2;138;200;11m@@: *@@\033[38;2;103;149;8m@@@@@@@@@@@@@@@@@@\033[38;2;138;200;11m@@:\t\tShell: \033[38;2;255;238;229m"
#define ART_WIN_09 "\t\033[38;2;138;200;11m      *@@\033[38;2;103;149;8m@@@@@@@@@@@@\033[38;2;138;200;11m@@: *@@\033[38;2;103;149;8m@@@@@@@@@@@@@@@@@@\033[38;2;138;200;11m@@-\t\tRoot: \033[38;2;255;238;229m"
#define ART_WIN_10 "\t\033[38;2;138;200;11m      *@@@@@@@@@@@@@@@@- #@@@@@@@@@@@@@@@@@@@@@@-\t\tCurrent: \033[38;2;255;238;229m"
#define ART_WIN_11 "\t\033[38;2;138;200;11m      =%#*#*#*#*###*##%: =%*******************#%:\t\tResolution: \033[38;2;255;238;229m"
#define ART_WIN_12 "\t\033[38;2;138;200;11m                                                 \t\tRefresh: \033[38;2;255;238;229m"
#define ART_WIN_13 "\t\033[38;2;138;200;11m      *@@@@@@@@@@@@@@@@- #@@@@@@@@@@@@@@@@@@@@@@-\t\tMemory: \033[38;2;255;238;229m"
#define ART_WIN_14 "\t\033[38;2;138;200;11m      *@@\033[38;2;103;149;8m@@@@@@@@@@@@\033[38;2;138;200;11m@@: *@@\033[38;2;103;149;8m@@@@@@@@@@@@@@@@@@\033[38;2;138;200;11m@@-\t\tPageFile: \033[38;2;255;238;229m"
#define ART_WIN_15 "\t\033[38;2;138;200;11m      +@@\033[38;2;103;149;8m@@@@@@@@@@@@\033[38;2;138;200;11m@@: *@@\033[38;2;103;149;8m@@@@@@@@@@@@@@@@@@\033[38;2;138;200;11m@@:\t\tVirtual: \033[38;2;255;238;229m"
#define ART_WIN_16 "\t\033[38;2;138;200;11m      +@@\033[38;2;103;149;8m@@@@@@@@@@@@\033[38;2;138;200;11m@@: *@@\033[38;2;103;149;8m@@@@@@@@@@@@@@@@@@\033[38;2;138;200;11m@@:\t\tDisk: \033[38;2;255;238;229m"
#define ART_WIN_17 "\t\033[38;2;138;200;11m      *@@\033[38;2;103;149;8m@@@@@@@@@@@@\033[38;2;138;200;11m@@. *@@\033[38;2;103;149;8m@@@@@@@@@@@@@@@@@@\033[38;2;138;200;11m@@:\t\tCPU: \033[38;2;255;238;229m"
#define ART_WIN_18 "\t\033[38;2;138;200;11m      *@@\033[38;2;103;149;8m@@@@@@@@@@@@\033[38;2;138;200;11m@@: *@@\033[38;2;103;149;8m@@@@@@@@@@@@@@@@@@\033[38;2;138;200;11m@@:\t\tGPU: \033[38;2;255;238;229m"
#define ART_WIN_19 "\t\033[38;2;138;200;11m      +@@@@@@@@@@@@@@@@: *@@\033[38;2;103;149;8m@@@@@@@@@@@@@@@@@@\033[38;2;138;200;11m@@:\n" \
                   "\t\033[38;2;138;200;11m            .:-=+*#%@@@- %@@@@@@@@@@\033[38;2;103;149;8m@@@@@@@@@@\033[38;2;138;200;11m@@:\t\t\033[40m   \033[41m   \033[42m   \033[43m   \033[44m   \033[45m   \033[46m   \033[47m   \033[0m\n" \
                   "\t\033[38;2;138;200;11m                          ::-=+*%%@@@@@@@@@@@@@@-\t\t\033[100m   \033[101m   \033[102m   \033[103m   \033[104m   \033[105m   \033[106m   \033[107m   \033[0m\n" \
                   "\t\033[38;2;138;200;11m                                        .:-=+#%@-\033[0m\n"

void getOSInfo(char* osInfo, char* osRoot, int bufferSize) {
    HKEY hKey;
    DWORD dwType = REG_SZ;
    DWORD dwSize = bufferSize;
    
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        char productName[256];
        DWORD productNameSize = sizeof(productName);
        
        if (RegQueryValueEx(hKey, "ProductName", NULL, &dwType, (LPBYTE)productName, &productNameSize) == ERROR_SUCCESS) {
            // Get build number
            char currentBuildNumber[256];
            DWORD currentBuildNumberSize = sizeof(currentBuildNumber);
            
            if (RegQueryValueEx(hKey, "CurrentBuildNumber", NULL, &dwType, (LPBYTE)currentBuildNumber, &currentBuildNumberSize) == ERROR_SUCCESS) {
                snprintf(osInfo, bufferSize, "%s Build %s", productName, currentBuildNumber);
            } else {
                snprintf(osInfo, bufferSize, "%s", productName);
            }
        } else {
            snprintf(osInfo, bufferSize, "Windows");
        }

        char productRoot[256];
        DWORD productRootSize = sizeof(productRoot);

        if (RegQueryValueEx(hKey, "SystemRoot", NULL, &dwType, (LPBYTE)productRoot, &productRootSize) == ERROR_SUCCESS) {
            snprintf(osRoot, bufferSize, productRoot);
        } else {
            snprintf(osRoot, bufferSize, "Unknown");
        }

        RegCloseKey(hKey);
    } else {
        snprintf(osInfo, bufferSize, "Windows");
    }
}

void getHostInfo(char* hostName, char* userName, int bufferSize) {
    DWORD size = bufferSize;
    GetComputerNameA(hostName, &size);
    
    size = bufferSize;
    GetUserNameA(userName, &size);
}

void getKernelInfo(char* kernelInfo, int bufferSize) {
    OSVERSIONINFOEX osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    
    if (GetVersionEx((OSVERSIONINFO*)&osvi)) {
        snprintf(kernelInfo, bufferSize, "NT %d.%d Build %d", 
                osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.dwBuildNumber);
    } else {
        snprintf(kernelInfo, bufferSize, "Unknown");
    }
}

void getUptime(char* uptime, int bufferSize) {
    DWORD tickCount = GetTickCount();
    int days = tickCount / (1000 * 60 * 60 * 24);
    int hours = (tickCount % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60);
    int minutes = (tickCount % (1000 * 60 * 60)) / (1000 * 60);
    
    if (days > 0) {
        snprintf(uptime, bufferSize, "%d days, %d hours, %d mins", days, hours, minutes);
    } else if (hours > 0) {
        snprintf(uptime, bufferSize, "%d hours, %d mins", hours, minutes);
    } else {
        snprintf(uptime, bufferSize, "%d mins", minutes);
    }
}

void getResolution(char* resolution, int bufferSize) {
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    snprintf(resolution, bufferSize, "%dx%d", width, height);
}

void getCPUInfo(char* cpuInfo, int bufferSize) {
    int CPUInfo[4] = {-1};
    char CPUBrandString[0x40] = {0};
    
    __cpuid(CPUInfo, 0x80000000);
    unsigned int nExIds = CPUInfo[0];
    
    if (nExIds >= 0x80000004) {
        __cpuid(CPUInfo, 0x80000002);
        memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
        __cpuid(CPUInfo, 0x80000003);
        memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
        __cpuid(CPUInfo, 0x80000004);
        memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
        
        // Clean up the string
        char* cleanString = CPUBrandString;
        while (*cleanString == ' ') cleanString++;
        
        snprintf(cpuInfo, bufferSize, "%s", cleanString);
    } else {
        snprintf(cpuInfo, bufferSize, "Unknown CPU");
    }
}

void getGPUInfo(char* gpuInfo, int bufferSize) {
    DISPLAY_DEVICE displayDevice;
    displayDevice.cb = sizeof(DISPLAY_DEVICE);
    
    if (EnumDisplayDevices(NULL, 0, &displayDevice, 0)) {
        snprintf(gpuInfo, bufferSize, "%s", displayDevice.DeviceString);
    } else {
        snprintf(gpuInfo, bufferSize, "Unknown GPU");
    }
}

void getFps(char* buffer, int bufferSize) {
    DEVMODE devMode;
    devMode.dmSize = sizeof(DEVMODE);
    devMode.dmDriverExtra = 0;
    
    if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode)) {
        // return devMode.dmDisplayFrequency;
        snprintf(buffer, bufferSize, "%d Hz", devMode.dmDisplayFrequency);
    } else {
        snprintf(buffer, bufferSize, "Unknown FPS");
    }
}

void getMemoryInfo(char* memoryInfo, char* pageInfo, char* virtualInfo, int bufferSize) {
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);

    if (GlobalMemoryStatusEx(&memoryStatus)) {
        double totalMB = memoryStatus.ullTotalPhys / (1024.0 * 1024.0);
        double availMB = memoryStatus.ullAvailPhys / (1024.0 * 1024.0);
        double usedMB  = totalMB - availMB;

        double totalPageMB = memoryStatus.ullTotalPageFile / (1024.0 * 1024.0);
        double availPageMB = memoryStatus.ullAvailPageFile / (1024.0 * 1024.0);

        double totalVirtMB = memoryStatus.ullTotalVirtual / (1024.0 * 1024.0);
        double availVirtMB = memoryStatus.ullAvailVirtual / (1024.0 * 1024.0);

        double usedPage = (double)(memoryStatus.ullTotalPageFile - memoryStatus.ullAvailPageFile);
        double percentPage = (usedPage * 100.0) / (double)memoryStatus.ullTotalPageFile;

        double usedVirt = memoryStatus.ullTotalVirtual - memoryStatus.ullAvailVirtual;
        double percentVirt = (usedVirt * 100.0) / memoryStatus.ullTotalVirtual;

        snprintf(memoryInfo, bufferSize, "%.0f / %.0f MiB (%.u%% used)", usedMB, totalMB, memoryStatus.dwMemoryLoad);
        snprintf(pageInfo, bufferSize, "%.0f / %.0f MiB (%.0f%% used)", totalPageMB - availPageMB, totalPageMB, percentPage);
        snprintf(virtualInfo, bufferSize, "%.0f / %.0f MiB (%.0f%% used)", totalVirtMB - availVirtMB, totalVirtMB, percentVirt);

    } else {

        snprintf(memoryInfo, bufferSize, "Unknown");
        snprintf(pageInfo, bufferSize, "Unknown");
        snprintf(virtualInfo, bufferSize, "Unknown");
    }
}

void getDiskInfo(char* diskInfo, int bufferSize) {
    ULARGE_INTEGER freeBytesAvailable, totalNumberOfBytes, totalNumberOfFreeBytes;
    
    if (GetDiskFreeSpaceEx("C:", &freeBytesAvailable, &totalNumberOfBytes, &totalNumberOfFreeBytes)) {
        double totalGB = totalNumberOfBytes.QuadPart / (1024.0 * 1024.0 * 1024.0);
        double freeGB = totalNumberOfFreeBytes.QuadPart / (1024.0 * 1024.0 * 1024.0);
        double usedGB = totalGB - freeGB;
        
        snprintf(diskInfo, bufferSize, "(C:) %.1fGB / %.1fGB (%.1fGB free)", 
                usedGB, totalGB, freeGB);
    } else {
        snprintf(diskInfo, bufferSize, "Unknown");
    }
}


void print_neuro(HANDLE hOut, DWORD written, char* shell) {

    char bufferA[256], bufferB[256], bufferC[256], bufferD[256];

    WriteConsoleA(hOut, ART_NEURO_00, sizeof(ART_NEURO_00) - 1, &written, NULL);
    WriteConsoleA(hOut, ART_NEURO_04, sizeof(ART_NEURO_04) - 1, &written, NULL);getHostInfo(bufferA, bufferB, 256);            fputs(bufferA, stdout); fputs("\033[38;2;156;106;71m @ \033[38;2;182;242;237m", stdout); fputs(bufferB, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_NEURO_05, sizeof(ART_NEURO_05) - 1, &written, NULL);
    WriteConsoleA(hOut, ART_NEURO_06, sizeof(ART_NEURO_06) - 1, &written, NULL);getOSInfo(bufferA, bufferB, 256);              fputs(bufferA, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_NEURO_07, sizeof(ART_NEURO_07) - 1, &written, NULL);getKernelInfo(bufferA, 256);                   fputs(bufferA, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_NEURO_08, sizeof(ART_NEURO_08) - 1, &written, NULL);getUptime(bufferA, 256);                       fputs(bufferA, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_NEURO_09, sizeof(ART_NEURO_09) - 1, &written, NULL);                                               fputs(shell, stdout);   fputs("\n", stdout);
    WriteConsoleA(hOut, ART_NEURO_10, sizeof(ART_NEURO_10) - 1, &written, NULL);                                               fputs(bufferB, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_NEURO_11, sizeof(ART_NEURO_11) - 1, &written, NULL);GetCurrentDirectory(256, bufferA);             fputs(bufferA, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_NEURO_12, sizeof(ART_NEURO_12) - 1, &written, NULL);getResolution(bufferA, 256);                   fputs(bufferA, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_NEURO_13, sizeof(ART_NEURO_13) - 1, &written, NULL);getFps(bufferA, 256);                          fputs(bufferA, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_NEURO_14, sizeof(ART_NEURO_14) - 1, &written, NULL);getMemoryInfo(bufferA, bufferB, bufferC, 256); fputs(bufferA, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_NEURO_15, sizeof(ART_NEURO_15) - 1, &written, NULL);                                               fputs(bufferB, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_NEURO_16, sizeof(ART_NEURO_16) - 1, &written, NULL);                                               fputs(bufferC, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_NEURO_17, sizeof(ART_NEURO_17) - 1, &written, NULL);getDiskInfo(bufferA, 256);                     fputs(bufferA, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_NEURO_18, sizeof(ART_NEURO_18) - 1, &written, NULL);getCPUInfo(bufferA, 256);                      fputs(bufferA, stdout); fputs("\n", stdout);                                    
    WriteConsoleA(hOut, ART_NEURO_19, sizeof(ART_NEURO_19) - 1, &written, NULL);getGPUInfo(bufferA, 256);                      fputs(bufferA, stdout); fputs("\n", stdout);      
    WriteConsoleA(hOut, ART_NEURO_20, sizeof(ART_NEURO_20) - 1, &written, NULL);
    exit(0);
}

void print_evil(HANDLE hOut, DWORD written, char* shell) {

    char bufferA[256], bufferB[256], bufferC[256], bufferD[256];

    WriteConsoleA(hOut, ART_EVIL_00, sizeof(ART_EVIL_00) - 1, &written, NULL);
    WriteConsoleA(hOut, ART_EVIL_04, sizeof(ART_EVIL_04) - 1, &written, NULL);getHostInfo(bufferA, bufferB, 256);            fputs(bufferA, stdout); fputs("\033[38;2;108;68;61m @ \033[38;2;176;25;64m", stdout); fputs(bufferB, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_EVIL_05, sizeof(ART_EVIL_05) - 1, &written, NULL);
    WriteConsoleA(hOut, ART_EVIL_06, sizeof(ART_EVIL_06) - 1, &written, NULL);getOSInfo(bufferA, bufferB, 256);              fputs(bufferA, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_EVIL_07, sizeof(ART_EVIL_07) - 1, &written, NULL);getKernelInfo(bufferA, 256);                   fputs(bufferA, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_EVIL_08, sizeof(ART_EVIL_08) - 1, &written, NULL);getUptime(bufferA, 256);                       fputs(bufferA, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_EVIL_09, sizeof(ART_EVIL_09) - 1, &written, NULL);                                               fputs(shell, stdout);   fputs("\n", stdout);
    WriteConsoleA(hOut, ART_EVIL_10, sizeof(ART_EVIL_10) - 1, &written, NULL);                                               fputs(bufferB, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_EVIL_11, sizeof(ART_EVIL_11) - 1, &written, NULL);GetCurrentDirectory(256, bufferA);             fputs(bufferA, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_EVIL_12, sizeof(ART_EVIL_12) - 1, &written, NULL);getResolution(bufferA, 256);                   fputs(bufferA, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_EVIL_13, sizeof(ART_EVIL_13) - 1, &written, NULL);getFps(bufferA, 256);                          fputs(bufferA, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_EVIL_14, sizeof(ART_EVIL_14) - 1, &written, NULL);getMemoryInfo(bufferA, bufferB, bufferC, 256); fputs(bufferA, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_EVIL_15, sizeof(ART_EVIL_15) - 1, &written, NULL);                                               fputs(bufferB, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_EVIL_16, sizeof(ART_EVIL_16) - 1, &written, NULL);                                               fputs(bufferC, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_EVIL_17, sizeof(ART_EVIL_17) - 1, &written, NULL);getDiskInfo(bufferA, 256);                     fputs(bufferA, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_EVIL_18, sizeof(ART_EVIL_18) - 1, &written, NULL);getCPUInfo(bufferA, 256);                      fputs(bufferA, stdout); fputs("\n", stdout);                                   
    WriteConsoleA(hOut, ART_EVIL_19, sizeof(ART_EVIL_19) - 1, &written, NULL);getGPUInfo(bufferA, 256);                      fputs(bufferA, stdout); fputs("\n", stdout);     
    WriteConsoleA(hOut, ART_EVIL_20, sizeof(ART_EVIL_20) - 1, &written, NULL);
    exit(0);
}

void print_win(HANDLE hOut, DWORD written, char* shell) {

    char bufferA[256], bufferB[256], bufferC[256], bufferD[256];

    WriteConsoleA(hOut, ART_WIN_01, sizeof(ART_WIN_01) - 1, &written, NULL);
    // WriteConsoleA(hOut, ART_WIN_02, sizeof(ART_WIN_02) - 1, &written, NULL);
    WriteConsoleA(hOut, ART_WIN_03, sizeof(ART_WIN_03) - 1, &written, NULL);getHostInfo(bufferA, bufferB, 256);            fputs(bufferA, stdout); fputs("\033[38;2;103;149;8m @ \033[38;2;255;183;3m", stdout); fputs(bufferB, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_WIN_04, sizeof(ART_WIN_04) - 1, &written, NULL);
    WriteConsoleA(hOut, ART_WIN_05, sizeof(ART_WIN_05) - 1, &written, NULL);getOSInfo(bufferA, bufferB, 256);              fputs(bufferA, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_WIN_06, sizeof(ART_WIN_06) - 1, &written, NULL);getKernelInfo(bufferA, 256);                   fputs(bufferA, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_WIN_07, sizeof(ART_WIN_07) - 1, &written, NULL);getUptime(bufferA, 256);                       fputs(bufferA, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_WIN_08, sizeof(ART_WIN_08) - 1, &written, NULL);                                               fputs(shell, stdout);   fputs("\n", stdout);
    WriteConsoleA(hOut, ART_WIN_09, sizeof(ART_WIN_09) - 1, &written, NULL);                                               fputs(bufferB, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_WIN_10, sizeof(ART_WIN_10) - 1, &written, NULL);GetCurrentDirectory(256, bufferA);             fputs(bufferA, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_WIN_11, sizeof(ART_WIN_11) - 1, &written, NULL);getResolution(bufferA, 256);                   fputs(bufferA, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_WIN_12, sizeof(ART_WIN_12) - 1, &written, NULL);getFps(bufferA, 256);                          fputs(bufferA, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_WIN_13, sizeof(ART_WIN_13) - 1, &written, NULL);getMemoryInfo(bufferA, bufferB, bufferC, 256); fputs(bufferA, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_WIN_14, sizeof(ART_WIN_14) - 1, &written, NULL);                                               fputs(bufferB, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_WIN_15, sizeof(ART_WIN_15) - 1, &written, NULL);                                               fputs(bufferC, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_WIN_16, sizeof(ART_WIN_16) - 1, &written, NULL);getDiskInfo(bufferA, 256);                     fputs(bufferA, stdout); fputs("\n", stdout);                                   
    WriteConsoleA(hOut, ART_WIN_17, sizeof(ART_WIN_17) - 1, &written, NULL);getCPUInfo(bufferA, 256);                      fputs(bufferA, stdout); fputs("\n", stdout);     
    WriteConsoleA(hOut, ART_WIN_18, sizeof(ART_WIN_18) - 1, &written, NULL);getGPUInfo(bufferA, 256);                      fputs(bufferA, stdout); fputs("\n", stdout);
    WriteConsoleA(hOut, ART_WIN_19, sizeof(ART_WIN_19) - 1, &written, NULL);
    exit(0);
}

int main(int argc, char *argv[]) {

    char title[256];

    DWORD written;
    DWORD dwMode = 0;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    
    if (GetConsoleTitleA(title, sizeof(title))) snprintf(title, 256, strrchr(title, '\\') + 1);
    else snprintf(title, 256, "Unknown");

    SetConsoleOutputCP(65001);

    title[20] = ' ';
    title[21] = '.';
    title[22] = '.';
    title[23] = '.';
    title[24] = '\0';

    if (argc > 1) {

        if (strcmp(argv[1], "neuro") == 0) print_neuro(hOut, written, title);
        else if (strcmp(argv[1], "evil") == 0) print_evil(hOut, written, title);
        else print_win(hOut, written, title);

    } else print_win(hOut, written, title);
    return 0;
}