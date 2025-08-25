#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <pdh.h>
#include <iphlpapi.h>
#include <intrin.h>
// #include <tchar.h>

#pragma comment(lib, "pdh.lib")
#pragma comment(lib, "iphlpapi.lib")

#define ART_NEURO_00 "\t\033[38;2;208;168;136m#***#**=***********#\033[38;2;156;106;71m+.\033[38;2;208;168;136m#**#####*#*\033[38;2;156;106;71m+\033[38;2;208;168;136m#*************%#\033[38;2;133;73;40m. ...\n" \
                     "\t\033[38;2;208;168;136m*=*#*==**#%%#%%%#*#%\033[38;2;156;106;71m -\033[38;2;208;168;136m#**%%%%%#%+\033[38;2;156;106;71m=*\033[38;2;208;168;136m%***#%%%%##+*###\033[38;2;133;73;40m: .. \n" \
                     "\t\033[38;2;208;168;136m=+##*.+##%%##*%*++#\033[38;2;156;106;71m+.+\033[38;2;208;168;136m#**%####*#*\033[38;2;156;106;71m--\033[38;2;208;168;136m%%+**#%%%%##+***#-\033[38;2;133;73;40m . \n" \
                     "\t\033[38;2;208;168;136m=**#=:####****+++*+\033[38;2;156;106;71m=*+\033[38;2;208;168;136m***#*****#*\033[38;2;156;106;71m--+\033[38;2;208;168;136m#*=*+*+**##*+#**#=\033[38;2;133;73;40m. \n" 
#define ART_NEURO_04 "\t\033[38;2;208;168;136m***#==#**+****#\033[38;2;156;106;71m+=\033[38;2;208;168;136m+\033[38;2;208;168;136m-%@\033[38;2;156;106;71m=*\033[38;2;208;168;136m*+********\033[38;2;156;106;71m:%=+\033[38;2;208;168;136m#++#**+++***+*+**:"
#define ART_NEURO_05 "\t\033[38;2;208;168;136m****+*****#*+#\033[38;2;156;106;71m=-\033[38;2;255;238;229m=-%@@\033[38;2;156;106;71m++\033[38;2;208;168;136m*+******#*\033[38;2;156;106;71m:\033[38;2;255;238;229m@@-*#\033[38;2;208;168;136m++##****+****+* "
#define ART_NEURO_06 "\t\033[38;2;208;168;136m*****+****#+*\033[38;2;156;106;71m==\033[38;2;255;238;229m+*@@@@\033[38;2;156;106;71m*==\033[38;2;208;168;136m*+#****##\033[38;2;156;106;71m:\033[38;2;255;238;229m%@@-+#\033[38;2;208;168;136m*+##*##%#*##++-"
#define ART_NEURO_07 "\t\033[38;2;208;168;136m+******##%*\033[38;2;156;106;71m===\033[38;2;255;238;229m=*@@@@@@\033[38;2;156;106;71m+:\033[38;2;208;168;136m++****+**\033[38;2;156;106;71m-#\033[38;2;255;238;229m@@@**\033[38;2;156;106;71m#--#\033[38;2;208;168;136m*+#@=:-++#="
#define ART_NEURO_08 "\t\033[38;2;208;168;136m*****+#*#\033[38;2;156;106;71m*.  :\033[38;2;255;238;229m.. .-+@@\033[38;2;156;106;71m#--\033[38;2;208;168;136m++##**+*\033[38;2;156;106;71m:*\033[38;2;255;238;229m@@@# .=. \033[38;2;156;106;71m:  :\033[38;2;208;168;136m%#-=.+#"
#define ART_NEURO_09 "\t\033[38;2;208;168;136m+****##\033[38;2;156;106;71m+. \033[38;2;255;238;229m-@+.@@-++=@@\033[38;2;156;106;71m+-=-\033[38;2;208;168;136m*##**\033[38;2;156;106;71m+--\033[38;2;255;238;229m@@\033[38;2;182;242;237m+  @%+@\033[38;2;255;238;229m#=\033[38;2;156;106;71m  :\033[38;2;208;168;136m=*%+-="
#define ART_NEURO_10 "\t\033[38;2;208;168;136m***##\033[38;2;156;106;71m*-:.\033[38;2;208;168;136m:\033[38;2;255;238;229m@@:\033[38;2;182;242;237m  -+  %\033[38;2;255;238;229m@@@@\033[38;2;156;106;71m=+=:\033[38;2;208;168;136m*##*\033[38;2;156;106;71m++*\033[38;2;255;238;229m=\033[38;2;182;242;237m@.  =: =\033[38;2;255;238;229m@@\033[38;2;156;106;71m\033[38;2;156;106;71m+.-\033[38;2;208;168;136m-==+=:"
#define ART_NEURO_11 "\t\033[38;2;208;168;136m*#*=\033[38;2;156;106;71m-:.\033[38;2;208;168;136m-\033[38;2;156;106;71m-\033[38;2;255;238;229m%@@\033[38;2;182;242;237m    .   \033[38;2;255;238;229m@@@@@\033[38;2;156;106;71m+#\033[38;2;255;238;229m*\033[38;2;156;106;71m:=\033[38;2;208;168;136m*#\033[38;2;156;106;71m+-\033[38;2;255;238;229m@#\033[38;2;182;242;237m+  :-   @\033[38;2;255;238;229m@@=\033[38;2;156;106;71m:\033[38;2;208;168;136m-+****"
#define ART_NEURO_12 "\t\033[38;2;208;168;136m=\033[38;2;156;106;71m--\033[38;2;208;168;136m-=--\033[38;2;156;106;71m=+\033[38;2;255;238;229m%@\033[38;2;182;242;237m*  +@@*: #\033[38;2;255;238;229m@@@@@\033[38;2;156;106;71m#%\033[38;2;255;238;229m@\033[38;2;156;106;71m+-+\033[38;2;208;168;136m*\033[38;2;156;106;71m-+\033[38;2;255;238;229m@@\033[38;2;182;242;237m.=%@#- +\033[38;2;255;238;229m@@%\033[38;2;156;106;71m:\033[38;2;208;168;136m=***+*"
#define ART_NEURO_13 "\t\033[38;2;208;168;136m+**###*\033[38;2;156;106;71m=-\033[38;2;255;238;229m@@@\033[38;2;182;242;237m+@@%%@#*@\033[38;2;255;238;229m@%@@@@\033[38;2;156;106;71m%\033[38;2;255;238;229m%@@\033[38;2;156;106;71m#++\033[38;2;208;168;136m\033[38;2;156;106;71m-*\033[38;2;255;238;229m@@\033[38;2;182;242;237m*%%@@#%\033[38;2;255;238;229m@@@\033[38;2;156;106;71m-\033[38;2;208;168;136m##****"
#define ART_NEURO_14 "\t\033[38;2;208;168;136m#****##\033[38;2;156;106;71m*:\033[38;2;255;238;229m#@@@\033[38;2;182;242;237m@@%%%%\033[38;2;255;238;229m%@%@@@@@@@@@@@\033[38;2;156;106;71m%#\033[38;2;255;238;229m=*%@%\033[38;2;182;242;237m%#%@\033[38;2;255;238;229m@@@@\033[38;2;156;106;71m-\033[38;2;208;168;136m+#**+*"
#define ART_NEURO_15 "\t\033[38;2;208;168;136m+#*****\033[38;2;156;106;71m*.\033[38;2;255;238;229m*@@@@\033[38;2;247;202;198m%%%@@@@@\033[38;2;255;238;229m%@%@%@%@%%@@@@%%%@%\033[38;2;247;202;198m@%@%%\033[38;2;255;238;229m@@\033[38;2;156;106;71m-\033[38;2;208;168;136m=#****"
#define ART_NEURO_16 "\t\033[38;2;208;168;136m=+*****#\033[38;2;156;106;71m.\033[38;2;255;238;229m:@%%\033[38;2;247;202;198m#%%%%%%%%\033[38;2;255;238;229m@%@%@%@@@@@%@@@@@\033[38;2;247;202;198m%%%%###%\033[38;2;255;238;229m@\033[38;2;156;106;71m:\033[38;2;208;168;136m=#***+"
#define ART_NEURO_17 "\t\033[38;2;208;168;136m++=+*#*#\033[38;2;156;106;71m+ \033[38;2;255;238;229m@@%\033[38;2;247;202;198m####%%%%%%\033[38;2;255;238;229m@%@@@%@@@%@%@%@\033[38;2;247;202;198m%@%%###%%\033[38;2;255;238;229m@\033[38;2;156;106;71m:\033[38;2;208;168;136m*****+"
#define ART_NEURO_18 "\t\033[38;2;208;168;136m**+==+#*#\033[38;2;156;106;71m=+\033[38;2;255;238;229m@@%\033[38;2;247;202;198m%%%%%%%%\033[38;2;255;238;229m@%@%@%@@@\033[38;2;144;98;69m*\033[38;2;255;238;229m@@@%@@@%\033[38;2;247;202;198m@%%%%%@\033[38;2;255;238;229m#\033[38;2;156;106;71m=\033[38;2;208;168;136m*#++=+"
#define ART_NEURO_19 "\t\033[38;2;156;106;71m+\033[38;2;208;168;136m+*#+-=++=\033[38;2;156;106;71m-*\033[38;2;255;238;229m@@@@@@@@@@%@%@%@@#\033[38;2;144;98;69m*+*\033[38;2;255;238;229m@@@@@%@@@@@@@@\033[38;2;156;106;71m+-\033[38;2;208;168;136m==-++="
#define ART_NEURO_20 "\t\033[38;2;156;106;71m-+\033[38;2;208;168;136m++#+=++= \033[38;2;156;106;71m:+\033[38;2;255;238;229m#@@@@@@@@@%@@@%@@@@@@@@@%@%@@@@@@\033[38;2;156;106;71m*-:\033[38;2;208;168;136m*++*+-"
#define ART_NEURO_21 "\t\033[38;2;156;106;71m -+\033[38;2;208;168;136m=++==+#+.\033[38;2;156;106;71m -=++**\033[38;2;255;238;229m%%@%@%@%@%@@@@@%@%@%@@@%##\033[38;2;156;106;71m=  \033[38;2;208;168;136m**===+:"
#define ART_NEURO_22 "\t\033[38;2;208;168;136m:\033[38;2;156;106;71m.-+\033[38;2;208;168;136m=--+==**.\033[38;2;156;106;71m.\033[38;2;255;238;229m@@%%@@@@@@@%@%@%@%@%@@@@@@@@@@\033[38;2;156;106;71m+  =\033[38;2;208;168;136m*=+:+-+"
#define ART_NEURO_23 "\t\033[38;2;208;168;136m:-\033[38;2;156;106;71m:-+\033[38;2;208;168;136m+--=++++=\033[38;2;156;106;71m=#\033[38;2;255;238;229m@@@@@@@@@@%@%@%@%@@@@@@@@\033[38;2;156;106;71m*=. -\033[38;2;208;168;136m+*+=:+=-*\n" \
                     "\t\033[38;2;208;168;136m:-=\033[38;2;156;106;71m.:=\033[38;2;208;168;136m++-.-====:\033[38;2;156;106;71m--:\033[38;2;255;238;229m:*%%%@@@@@@@@@@@@%\033[38;2;156;106;71m*+-. ...\033[38;2;208;168;136m-+-..----=\n" \
                     "\t\033[38;2;208;168;136m:-=\033[38;2;156;106;71m  :=\033[38;2;208;168;136m--=-==++==\033[38;2;156;106;71m==-\033[38;2;255;238;229m#%#####%%%%%\033[38;2;156;106;71m*+--::-=:--- :\033[38;2;208;168;136m+=.:.+*+*\033[0m\n"
// #define ART_NEURO_26 "\t\033[0m"

#define ART_EVIL_00 "\t\033[38;2;149;107;100m#***#**=***********#\033[38;2;108;68;61m+.\033[38;2;149;107;100m#**#####*#*\033[38;2;108;68;61m+\033[38;2;149;107;100m#*************%#\033[38;2;133;73;40m. ...\n"
#define ART_EVIL_01 "\t\033[38;2;149;107;100m*=*#*==**#%%#%%%#*#%\033[38;2;108;68;61m -\033[38;2;149;107;100m#**%%%%%#%+\033[38;2;108;68;61m=*\033[38;2;149;107;100m%***#%%%%##+*###\033[38;2;133;73;40m: .."
#define ART_EVIL_02 "\t\033[38;2;149;107;100m=+##*.+##%%##*%*++#\033[38;2;108;68;61m+.+\033[38;2;149;107;100m#**%####*#*\033[38;2;108;68;61m--\033[38;2;149;107;100m%%+**#%%%%##+***#-\033[38;2;133;73;40m ."
#define ART_EVIL_03 "\t\033[38;2;149;107;100m=**#=:####****+++*+\033[38;2;108;68;61m=*+\033[38;2;149;107;100m***#*****#*\033[38;2;108;68;61m--+\033[38;2;149;107;100m#*=*+*+**##*+#**#=\033[38;2;133;73;40m."
#define ART_EVIL_04 "\t\033[38;2;149;107;100m***#==#**+****#\033[38;2;108;68;61m+=\033[38;2;149;107;100m+\033[38;2;149;107;100m-%@\033[38;2;108;68;61m=*\033[38;2;149;107;100m*+********\033[38;2;108;68;61m:%=+\033[38;2;149;107;100m#++#**+++***+*+**:"
#define ART_EVIL_05 "\t\033[38;2;149;107;100m****+*****#*+#\033[38;2;108;68;61m=-\033[38;2;254;243;236m=-%@@\033[38;2;108;68;61m++\033[38;2;149;107;100m*+******#*\033[38;2;108;68;61m:\033[38;2;254;243;236m@@-*#\033[38;2;149;107;100m++##****+****+* "
#define ART_EVIL_06 "\t\033[38;2;149;107;100m*****+****#+*\033[38;2;108;68;61m==\033[38;2;254;243;236m+*@@@@\033[38;2;108;68;61m*==\033[38;2;149;107;100m*+#****##\033[38;2;108;68;61m:\033[38;2;254;243;236m%@@-+#\033[38;2;149;107;100m*+##*##%#*##++-"
#define ART_EVIL_07 "\t\033[38;2;149;107;100m+******##%*\033[38;2;108;68;61m===\033[38;2;254;243;236m=*@@@@@@\033[38;2;108;68;61m+:\033[38;2;149;107;100m++****+**\033[38;2;108;68;61m-#\033[38;2;254;243;236m@@@**\033[38;2;108;68;61m#--#\033[38;2;149;107;100m*+#@=:-++#="
#define ART_EVIL_08 "\t\033[38;2;149;107;100m*****+#*#\033[38;2;108;68;61m*.  :\033[38;2;254;243;236m.. .-+@@\033[38;2;108;68;61m#--\033[38;2;149;107;100m++##**+*\033[38;2;108;68;61m:*\033[38;2;254;243;236m@@@# .=. \033[38;2;108;68;61m:  :\033[38;2;149;107;100m%#-=.+#"
#define ART_EVIL_09 "\t\033[38;2;149;107;100m+****##\033[38;2;108;68;61m+. \033[38;2;254;243;236m-@+.@@-++=@@\033[38;2;108;68;61m+-=-\033[38;2;149;107;100m*##**\033[38;2;108;68;61m+--\033[38;2;254;243;236m@@\033[38;2;176;25;64m+  @%+@\033[38;2;254;243;236m#=\033[38;2;108;68;61m  :\033[38;2;149;107;100m=*%+-="
#define ART_EVIL_10 "\t\033[38;2;149;107;100m***##\033[38;2;108;68;61m*-:.\033[38;2;149;107;100m:\033[38;2;254;243;236m@@:\033[38;2;176;25;64m  -+  %\033[38;2;254;243;236m@@@@\033[38;2;108;68;61m=+=:\033[38;2;149;107;100m*##*\033[38;2;108;68;61m++*\033[38;2;254;243;236m=\033[38;2;176;25;64m@.  =: =\033[38;2;254;243;236m@@\033[38;2;108;68;61m\033[38;2;108;68;61m+.-\033[38;2;149;107;100m-==+=:"
#define ART_EVIL_11 "\t\033[38;2;149;107;100m*#*=\033[38;2;108;68;61m-:.\033[38;2;149;107;100m-\033[38;2;108;68;61m-\033[38;2;254;243;236m%@@\033[38;2;176;25;64m    .   \033[38;2;254;243;236m@@@@@\033[38;2;108;68;61m+#\033[38;2;254;243;236m*\033[38;2;108;68;61m:=\033[38;2;149;107;100m*#\033[38;2;108;68;61m+-\033[38;2;254;243;236m@#\033[38;2;176;25;64m+  :-   @\033[38;2;254;243;236m@@=\033[38;2;108;68;61m:\033[38;2;149;107;100m-+****"
#define ART_EVIL_12 "\t\033[38;2;149;107;100m=\033[38;2;108;68;61m--\033[38;2;149;107;100m-=--\033[38;2;108;68;61m=+\033[38;2;254;243;236m%@\033[38;2;176;25;64m*  +@@*: #\033[38;2;254;243;236m@@@@@\033[38;2;108;68;61m#%\033[38;2;254;243;236m@\033[38;2;108;68;61m+-+\033[38;2;149;107;100m*\033[38;2;108;68;61m-+\033[38;2;254;243;236m@@\033[38;2;176;25;64m.=%@#- +\033[38;2;254;243;236m@@%\033[38;2;108;68;61m:\033[38;2;149;107;100m=***+*"
#define ART_EVIL_13 "\t\033[38;2;149;107;100m+**###*\033[38;2;108;68;61m=-\033[38;2;254;243;236m@@@\033[38;2;176;25;64m+@@%%@#*@\033[38;2;254;243;236m@%@@@@\033[38;2;108;68;61m%\033[38;2;254;243;236m%@@\033[38;2;108;68;61m#++\033[38;2;149;107;100m\033[38;2;108;68;61m-*\033[38;2;254;243;236m@@\033[38;2;176;25;64m*%%@@#%\033[38;2;254;243;236m@@@\033[38;2;108;68;61m-\033[38;2;149;107;100m##****"
#define ART_EVIL_14 "\t\033[38;2;149;107;100m#****##\033[38;2;108;68;61m*:\033[38;2;254;243;236m#@@@\033[38;2;176;25;64m@@%%%%\033[38;2;254;243;236m%@%@@@@@@@@@@@\033[38;2;108;68;61m%#\033[38;2;254;243;236m=*%@%\033[38;2;176;25;64m%#%@\033[38;2;254;243;236m@@@@\033[38;2;108;68;61m-\033[38;2;149;107;100m+#**+*"
#define ART_EVIL_15 "\t\033[38;2;149;107;100m+#*****\033[38;2;108;68;61m*.\033[38;2;254;243;236m*@@@@\033[38;2;247;202;198m%%%@@@@@\033[38;2;254;243;236m%@%@%@%@%%@@@@%%%@%\033[38;2;247;202;198m@%@%%\033[38;2;254;243;236m@@\033[38;2;108;68;61m-\033[38;2;149;107;100m=#****"
#define ART_EVIL_16 "\t\033[38;2;149;107;100m=+*****#\033[38;2;108;68;61m.\033[38;2;254;243;236m:@%%\033[38;2;247;202;198m#%%%%%%%%\033[38;2;254;243;236m@%@%@%@@@@@%@@@@@\033[38;2;247;202;198m%%%%###%\033[38;2;254;243;236m@\033[38;2;108;68;61m:\033[38;2;149;107;100m=#***+"
#define ART_EVIL_17 "\t\033[38;2;149;107;100m++=+*#*#\033[38;2;108;68;61m+ \033[38;2;254;243;236m@@%\033[38;2;247;202;198m####%%%%%%\033[38;2;254;243;236m@%@@@%@@@%@%@%@\033[38;2;247;202;198m%@%%###%%\033[38;2;254;243;236m@\033[38;2;108;68;61m:\033[38;2;149;107;100m*****+"
#define ART_EVIL_18 "\t\033[38;2;149;107;100m**+==+#*#\033[38;2;108;68;61m=+\033[38;2;254;243;236m@@%\033[38;2;247;202;198m%%%%%%%%\033[38;2;254;243;236m@%@%@%@@@\033[38;2;144;98;69m*\033[38;2;254;243;236m@@@%@@@%\033[38;2;247;202;198m@%%%%%@\033[38;2;254;243;236m#\033[38;2;108;68;61m=\033[38;2;149;107;100m*#++=+"
#define ART_EVIL_19 "\t\033[38;2;108;68;61m+\033[38;2;149;107;100m+*#+-=++=\033[38;2;108;68;61m-*\033[38;2;254;243;236m@@@@@@@@@@%@%@%@@#\033[38;2;144;98;69m*+*\033[38;2;254;243;236m@@@@@%@@@@@@@@\033[38;2;108;68;61m+-\033[38;2;149;107;100m==-++="
#define ART_EVIL_20 "\t\033[38;2;108;68;61m-+\033[38;2;149;107;100m++#+=++= \033[38;2;108;68;61m:+\033[38;2;254;243;236m#@@@@@@@@@%@@@%@@@@@@@@@%@%@@@@@@\033[38;2;108;68;61m*-:\033[38;2;149;107;100m*++*+-"
#define ART_EVIL_21 "\t\033[38;2;108;68;61m -+\033[38;2;149;107;100m=++==+#+.\033[38;2;108;68;61m -=++**\033[38;2;254;243;236m%%@%@%@%@%@@@@@%@%@%@@@%##\033[38;2;108;68;61m=  \033[38;2;149;107;100m**===+:"
#define ART_EVIL_22 "\t\033[38;2;149;107;100m:\033[38;2;108;68;61m.-+\033[38;2;149;107;100m=--+==**.\033[38;2;108;68;61m.\033[38;2;254;243;236m@@%%@@@@@@@%@%@%@%@%@@@@@@@@@@\033[38;2;108;68;61m+  =\033[38;2;149;107;100m*=+:+-+"
#define ART_EVIL_23 "\t\033[38;2;149;107;100m:-\033[38;2;108;68;61m:-+\033[38;2;149;107;100m+--=++++=\033[38;2;108;68;61m=#\033[38;2;254;243;236m@@@@@@@@@@%@%@%@%@@@@@@@@\033[38;2;108;68;61m*=. -\033[38;2;149;107;100m+*+=:+=-*"
#define ART_EVIL_24 "\t\033[38;2;149;107;100m:-=\033[38;2;108;68;61m.:=\033[38;2;149;107;100m++-.-====:\033[38;2;108;68;61m--:\033[38;2;254;243;236m:*%%%@@@@@@@@@@@@%\033[38;2;108;68;61m*+-. ...\033[38;2;149;107;100m-+-..----="
#define ART_EVIL_25 "\t\033[38;2;149;107;100m:-=\033[38;2;108;68;61m  :=\033[38;2;149;107;100m--=-==++==\033[38;2;108;68;61m==-\033[38;2;254;243;236m#%#####%%%%%\033[38;2;108;68;61m*+--::-=:--- :\033[38;2;149;107;100m+=.:.+*+*"
#define ART_EVIL_26 "\t\033[0m"



void getOSInfo(char* osInfo, int bufferSize) {
    HKEY hKey;
    DWORD dwType = REG_SZ;
    DWORD dwSize = bufferSize;
    
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 
                     0, KEY_READ, &hKey) == ERROR_SUCCESS) {
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

void getShellInfo(char* shellInfo, int bufferSize) {
    const char* comspec = getenv("COMSPEC");
    if (comspec != NULL) {
        // Extract just the executable name from the path
        const char* name = strrchr(comspec, '\\');
        if (name != NULL) {
            snprintf(shellInfo, bufferSize, "%s", name + 1);
        } else {
            snprintf(shellInfo, bufferSize, "%s", comspec);
        }
    } else {
        snprintf(shellInfo, bufferSize, "cmd.exe");
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

void getFps(char* buffer, int size) {
    DEVMODE devMode;
    devMode.dmSize = sizeof(DEVMODE);
    devMode.dmDriverExtra = 0;
    
    if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode)) {
        // return devMode.dmDisplayFrequency;
        snprintf(buffer, size, "%d Hz", devMode.dmDisplayFrequency);
    } else {
        snprintf(buffer, size, "Unknown FPS");
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


void print_neuro(HANDLE hOut, DWORD written) {

    char bufferA[256], bufferB[256], bufferC[256], bufferD[256];

    



    
    
    
    WriteConsoleA(hOut, ART_NEURO_00, sizeof(ART_NEURO_00) - 1, &written, NULL);
    WriteConsoleA(hOut, ART_NEURO_04, sizeof(ART_NEURO_04) - 1, &written, NULL);getHostInfo(bufferA, bufferB, 256);            printf("\t\t%s\033[38;2;156;106;71m @ \033[38;2;182;242;237m%s\n", bufferA, bufferB);
    WriteConsoleA(hOut, ART_NEURO_05, sizeof(ART_NEURO_05) - 1, &written, NULL);                                               printf("\t\t\033[38;2;156;106;71m-----------------------\n");
    WriteConsoleA(hOut, ART_NEURO_06, sizeof(ART_NEURO_06) - 1, &written, NULL);getOSInfo(bufferA, 256);                       printf("\t\tOS: \033[38;2;255;238;229m%s\n", bufferA);
    WriteConsoleA(hOut, ART_NEURO_07, sizeof(ART_NEURO_07) - 1, &written, NULL);getKernelInfo(bufferA, 256);                   printf("\t\tKernel: \033[38;2;255;238;229m%s\n", bufferA);
    WriteConsoleA(hOut, ART_NEURO_08, sizeof(ART_NEURO_08) - 1, &written, NULL);getUptime(bufferA, 256);                       printf("\t\tUptime: \033[38;2;255;238;229m%s\n", bufferA);
    WriteConsoleA(hOut, ART_NEURO_09, sizeof(ART_NEURO_09) - 1, &written, NULL);getShellInfo(bufferA, 256);                    printf("\t\tShell: \033[38;2;255;238;229m%s\n", bufferA);
    WriteConsoleA(hOut, ART_NEURO_10, sizeof(ART_NEURO_10) - 1, &written, NULL);                                               printf("\t\tRoot: \033[38;2;255;238;229mC:\\Windows\n");
    WriteConsoleA(hOut, ART_NEURO_11, sizeof(ART_NEURO_11) - 1, &written, NULL);GetCurrentDirectory(256, bufferA);             printf("\t\tCurrent: \033[38;2;255;238;229m%s\n", bufferA);
    WriteConsoleA(hOut, ART_NEURO_12, sizeof(ART_NEURO_12) - 1, &written, NULL);getResolution(bufferA, 256);                   printf("\t\tResolution: \033[38;2;255;238;229m%s\n", bufferA);
    WriteConsoleA(hOut, ART_NEURO_13, sizeof(ART_NEURO_13) - 1, &written, NULL);getFps(bufferA, 256);                          printf("\t\tRefresh: \033[38;2;255;238;229m%s\n", bufferA);
    WriteConsoleA(hOut, ART_NEURO_14, sizeof(ART_NEURO_14) - 1, &written, NULL);getMemoryInfo(bufferA, bufferB, bufferC, 256); printf("\t\tMemory: \033[38;2;255;238;229m%s\n", bufferA);
    WriteConsoleA(hOut, ART_NEURO_15, sizeof(ART_NEURO_15) - 1, &written, NULL);                                               printf("\t\tPageFile: \033[38;2;255;238;229m%s\n", bufferB);
    WriteConsoleA(hOut, ART_NEURO_16, sizeof(ART_NEURO_16) - 1, &written, NULL);                                               printf("\t\tVirtual: \033[38;2;255;238;229m%s\n", bufferC);
    WriteConsoleA(hOut, ART_NEURO_17, sizeof(ART_NEURO_17) - 1, &written, NULL);getDiskInfo(bufferA, 256);                     printf("\t\tDisk: \033[38;2;255;238;229m%s\n", bufferA);
    WriteConsoleA(hOut, ART_NEURO_18, sizeof(ART_NEURO_18) - 1, &written, NULL);getCPUInfo(bufferA, 256);                      printf("\t\tCPU: \033[38;2;255;238;229m%s\n", bufferA);                                    
    WriteConsoleA(hOut, ART_NEURO_19, sizeof(ART_NEURO_19) - 1, &written, NULL);getGPUInfo(bufferA, 256);                      printf("\t\tGPU: \033[38;2;255;238;229m%s\n", bufferA);      
    WriteConsoleA(hOut, ART_NEURO_20, sizeof(ART_NEURO_20) - 1, &written, NULL);printf("\t\t\n");
    WriteConsoleA(hOut, ART_NEURO_21, sizeof(ART_NEURO_21) - 1, &written, NULL);printf("\t\t\033[40m   \033[41m   \033[42m   \033[43m   \033[44m   \033[45m   \033[46m   \033[47m   \033[0m\n");
    WriteConsoleA(hOut, ART_NEURO_22, sizeof(ART_NEURO_22) - 1, &written, NULL);printf("\t\t\033[100m   \033[101m   \033[102m   \033[103m   \033[104m   \033[105m   \033[106m   \033[107m   \033[0m\n");
    WriteConsoleA(hOut, ART_NEURO_23, sizeof(ART_NEURO_23) - 1, &written, NULL);
}


int main(void) {

    DWORD written;
    DWORD dwMode = 0;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    
    print_neuro(hOut, written);
    // WriteConsoleA(hOut, ART_NEURO, sizeof(ART_NEURO) - 1, &written, NULL);
    // WriteConsoleA(hOut, ART_EVIL, sizeof(ART_EVIL) - 1, &written, NULL);

    SetConsoleOutputCP(65001);
    
    char buffer[256];
    
    // getOSInfo(buffer, sizeof(buffer));
    // printf("OS: %s\n", buffer);
    
    // Host and username
    // char hostName[256], userName[256];
    // getHostInfo(hostName, userName, sizeof(hostName));
    // printf("User: %s\n", userName);
    // printf("Host: %s\n", hostName);
    
    // Kernel version
    // getKernelInfo(buffer, sizeof(buffer));
    // printf("Kernel: %s\n", buffer);
    
    // Uptime
    // getUptime(buffer, sizeof(buffer));
    // printf("Uptime: %s\n", buffer);
    
    // Shell information
    // getShellInfo(buffer, sizeof(buffer));
    // printf("Shell: %s\n", buffer);
    
    // Resolution
    // getResolution(buffer, sizeof(buffer));
    // printf("Resolution: %s\n", buffer);
    
    // CPU information
    // getCPUInfo(buffer, sizeof(buffer));
    // printf("CPU: %s\n", buffer);
    
    // GPU information
    // getGPUInfo(buffer, sizeof(buffer));
    // printf("GPU: %s\n", buffer);
    
    // Memory information
    // getMemoryInfo(buffer, sizeof(buffer));
    // printf("Memory: %s\n", buffer);
    
    // Disk information
    // getDiskInfo(buffer, sizeof(buffer));
    // printf("Disk: %s\n", buffer);
    







    // TCHAR modulePath[MAX_PATH];
    // TCHAR currentDirectory[MAX_PATH];
    
    // // Get the path of the current executable
    // if (GetModuleFileName(NULL, modulePath, MAX_PATH) == 0) {
    //     printf("Error getting module filename: %lu\n", GetLastError());
    //     return 1;
    // }
    
    // // Extract just the executable name from the full path
    // TCHAR* exeName = _tcsrchr(modulePath, '\\');
    // if (exeName != NULL) {
    //     exeName++; // Move past the backslash
    // } else {
    //     exeName = modulePath; // Use the full path if no backslash found
    // }
    
    // // Get the current working directory
    // if (GetCurrentDirectory(MAX_PATH, currentDirectory) == 0) {
    //     printf("Error getting current directory: %lu\n", GetLastError());
    //     return 1;
    // }
    
    // // Print the results
    // _tprintf(_T("Application: %s\n"), exeName);
    // _tprintf(_T("Path: %s\n"), currentDirectory);













    return 0;
}