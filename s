===>Got return -- value: 0

fdf
fdf
Export 4: ✅
fdf
fdf
Export 5: ✅
fdf
fdf
Export 6: ✅
fdf
fdf
Export 7: ✅
fdf
fdf
Export 8 ❌ export a++=
===>Expeced return -- value: 1

===>Got return -- value: 0

fdf
fdf
Export 9: ✅
fdf
fdf
Export 10: ✅
fdf
fdf
Export 11 ❌ export 5asd=
===>Expeced return -- value: 1

===>Got return -- value: 0

fdf
fdf
Export 12 ❌ export 5asd_+=
===>Expeced return -- value: 1

===>Got return -- value: 0

fdf
fdf
Export 13 ❌ export +HELLO=123 +A 123 55
===>Expeced return -- value: 1

===>Got return -- value: 0

fdf
fdf
Export 14: ✅
fdf
fdf
Export 15: ✅
fdf
fdf
Export 16 ❌ export HELLO-=123
===>Expeced return -- value: 1

===>Got return -- value: 0

fdf
fdf
Export 17 ❌ export =
===>Expeced return -- value: 1

===>Got return -- value: 0

fdf
fdf
Export 18 ❌ export 123
===>Expeced return -- value: 1

===>Got return -- value: 0

fdf
fdf
Export 19 ❌ export holola | echo $holola
===>Expeced return -- value: 0


===>Got return -- value: 0

fdf
fdf
Export 21 ❌ export a++=a
===>Expeced return -- value: 1

===>Got return -- value: 0

fdf
fdf
Export 22 ❌ export 9k=a
===>Expeced return -- value: 1

===>Got return -- value: 0

fdf
fdf
Export 23 ❌ export =sdfsf
===>Expeced return -- value: 1

===>Got return -- value: 0

fdf
fdf
Unset 1: ✅
fdf
fdf
Unset 2: ✅
fdf
fdf
Unset 3: ✅
fdf
fdf
Unset 4: ✅
fdf
fdf
Unset 5: ✅
fdf
fdf
Unset 6 ❌ unset ++
===>Expeced return -- value: 1

===>Got return -- value: 0

fdf
fdf
Unset 7 ❌ unset +=gwllo
===>Expeced return -- value: 1

===>Got return -- value: 0

fdf
fdf
Unset 8 ❌ unset 3gwllo
===>Expeced return -- value: 1

===>Got return -- value: 0

fdf
fdf
Unset 9: ✅
fdf
fdf
Unset 10 ❌ unset pwd | echo $pwd
===>Expeced return -- value: 0


===>Got return -- value: 0

fdf
fdf
Unset 11 ❌ unset pwd"'" | echo $pwd
===>Expeced return -- value: 0


===>Got return -- value: 0

fdf
fdf
Unset 13 ❌ unset hello+=
===>Expeced return -- value: 1

===>Got return -- value: 0

fdf
fdf
Unset 14: ✅
fdf
fdf
Unset 15 ❌ unset "$sdfsdf"
===>Expeced return -- value: 1

===>Got return -- value: 0

fdf
fdf
Unset 16: ✅
fdf
fdf
cd 1: ✅
fdf
fdf
cd 2 ❌ cd ...
===>Expeced return -- value: 1

===>Got return -- value: 0

fdf
fdf
cd 3: ✅
fdf
fdf
cd 4: ✅
fdf
fdf
cd 5: ✅
fdf
fdf
cd 6: ✅
fdf
fdf
cd 7: ✅
fdf
fdf
cd 8: ✅
fdf
fdf
cd 9 ❌ cd /testtt
===>Expeced return -- value: 1

===>Got return -- value: 0

fdf
fdf
cd 10 ❌ cd /exam
===>Expeced return -- value: 1

===>Got return -- value: 0

fdf
fdf
Env 1 ❌ env | grep ^HOME
===>Expeced return -- value: 0
HOMEBREW_TEMP=/tmp/mal-mora/Homebrew/Temp
HOMEBREW_CACHE=/tmp/mal-mora/Homebrew/Caches
HOME=/Users/mal-mora

===>Got return -- value: 0
HOMEBREW_TEMP=/tmp/mal-mora/Homebrew/Temp
HOMEBREW_CACHE=/tmp/mal-mora/Homebrew/Caches

fdf
fdf
Env 2 ❌ env | grep ^HOME | cat
===>Expeced return -- value: 0
HOMEBREW_TEMP=/tmp/mal-mora/Homebrew/Temp
HOMEBREW_CACHE=/tmp/mal-mora/Homebrew/Caches
HOME=/Users/mal-mora

===>Got return -- value: 0
HOMEBREW_TEMP=/tmp/mal-mora/Homebrew/Temp
HOMEBREW_CACHE=/tmp/mal-mora/Homebrew/Caches

fdf
fdf
Exit 1: ✅
fdf
fdf
Exit 2: ✅
fdf
fdf
Exit 3 ❌ exit 123 | echo $?
===>Expeced return -- value: 0
0

===>Got return -- value: 0

fdf
fdf
Exit 4: ✅
fdf
fdf
Exit 5: ✅
fdf
fdf
Exit 6: ✅
fdf
fdf
Exit 7: ✅
fdf
fdf
Exit 8: ✅
fdf
fdf
Exit 9: ✅
fdf
fdf
Exit 10: ✅
fdf
fdf
Exit 11: ✅
fdf
fdf
Exit 12 ❌ exit 42 world
===>Expeced return -- value: 1

===>Got return -- value: 42

fdf
fdf
Exit 13 ❌ exit 42  | echo hello
===>Expeced return -- value: 0
hello

===>Got return -- value: 0

fdf
fdf
Exit 14 ❌ exit 42  | exit 1
===>Expeced return -- value: 1

===>Got return -- value: 0

fdf
fdf
Exit 15: ✅
fdf
fdf
Exit 16: ✅
fdf
fdf
Exit 17 ❌ exit 88 88
===>Expeced return -- value: 1

===>Got return -- value: 88

fdf
fdf
Exit 19: ✅
fdf
fdf
Exit 20: ✅
fdf
fdf
Exit 21: ✅
fdf
fdf
Exit 22: ✅
fdf
fdf
Exit 23: ✅
fdf
fdf
Exit 24: ✅

█▀█ █▀▀ █▀▄ █ █▀█ █▀▀ █▀▀ ▀█▀ █ █▀█ █▄░█
█▀▄ ██▄ █▄▀ █ █▀▄ ██▄ █▄▄ ░█░ █ █▄█ █░▀█ 

fdf
fdf
Redirection 1 ❌ grep hi <./test_files/infile
===>Expeced return -- value: 1

===>Got return -- value: 0

fdf
fdf
Redirection 2 ❌ grep hi "<infile" <         ./test_files/infile
===>Expeced return -- value: 1

===>Got return -- value: 0

fdf
fdf
Redirection 3 ❌ echo hi < ./test_files/infile bye bye
===>Expeced return -- value: 1

===>Got return -- value: 0

fdf
fdf
Redirection 4 ❌ grep hi <./test_files/infile_big <./test_files/infile
===>Expeced return -- value: 1

===>Got return -- value: 0

fdf
fdf
Redirection 5 ❌ echo <"./test_files/infile" "bonjour       42"
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 6 ❌ cat <"./test_files/file name with spaces"
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 7 ❌ cat <./test_files/infile_big ./test_files/infile
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 8 ❌ cat <"1""2""3""4""5"
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 9 ❌ echo <"./test_files/infile" <missing <"./test_files/infile"
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 10 ❌ echo <missing <"./test_files/infile" <missing
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 11 ❌ cat <"./test_files/infile"
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 12 ❌ echo <"./test_files/infile_big" | cat <"./test_files/infile"
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 13 ❌ echo <"./test_files/infile_big" | cat "./test_files/infile"
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 14 ❌ echo <"./test_files/infile_big" | echo <"./test_files/infile"
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 15 ❌ echo hi | cat <"./test_files/infile"
===>Expeced return -- value: 1

===>Got return -- value: 0

fdf
fdf
Redirection 16 ❌ echo hi | cat "./test_files/infile"
===>Expeced return -- value: 1

===>Got return -- value: 0

fdf
fdf
Redirection 17: ✅
fdf
fdf
Redirection 18 ❌ cat <"./test_files/infile" | grep hello
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 19 ❌ cat <"./test_files/infile_big" | echo hi
===>Expeced return -- value: 0
hi

===>Got return -- value: 134

fdf
fdf
Redirection 20 ❌ cat <missing
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 21 ❌ cat <missing | cat
===>Expeced return -- value: 0

===>Got return -- value: 134

fdf
fdf
Redirection 22 ❌ cat <missing | echo oi
===>Expeced return -- value: 0
oi

===>Got return -- value: 134

fdf
fdf
Redirection 23 ❌ cat <missing | cat <"./test_files/infile"
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 24 ❌ echo <123 <456 hi | echo 42
===>Expeced return -- value: 0
42

===>Got return -- value: 134

fdf
fdf
Redirection 25 ❌ ls >./outfiles/outfile01
===>Expeced return -- value: 0

===>Got return -- value: 134

fdf
fdf
Redirection 26 ❌ ls >         ./outfiles/outfile01
===>Expeced return -- value: 0

===>Got return -- value: 134

fdf
fdf
Redirection 27: ✅
fdf
fdf
Redirection 28 ❌ ls >./outfiles/outfile01 >./outfiles/outfile02
===>Expeced return -- value: 0

===>Got return -- value: 134

fdf
fdf
Redirection 29 ❌ ls >./outfiles/outfile01 >./test_files/invalid_permission
===>Expeced return -- value: 0

===>Got return -- value: 134

fdf
fdf
Redirection 30 ❌ ls >"./outfiles/outfile with spaces"
===>Expeced return -- value: 0

===>Got return -- value: 134

fdf
fdf
Redirection 31 ❌ ls >"./outfiles/outfile""1""2""3""4""5"
===>Expeced return -- value: 0

===>Got return -- value: 134

fdf
fdf
Redirection 32 ❌ ls >"./outfiles/outfile01" >./test_files/invalid_permission >"./outfiles/outfile02"
===>Expeced return -- value: 0

===>Got return -- value: 134

fdf
fdf
Redirection 33 ❌ ls >./test_files/invalid_permission >"./outfiles/outfile01" >./test_files/invalid_permission
===>Expeced return -- value: 0

===>Got return -- value: 134

fdf
fdf
Redirection 34 ❌ cat <"./test_files/infile" >"./outfiles/outfile01"
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 35 ❌ echo hi >./outfiles/outfile01 | echo bye
===>Expeced return -- value: 0
bye

===>Got return -- value: 0

fdf
fdf
Redirection 36 ❌ echo hi >./outfiles/outfile01 >./outfiles/outfile02 | echo bye
===>Expeced return -- value: 0
bye

===>Got return -- value: 0

fdf
fdf
Redirection 37: ✅
fdf
fdf
Redirection 38: ✅
fdf
fdf
Redirection 39: ✅
fdf
fdf
Redirection 40 ❌ echo hi >./outfiles/outfile01 >./test_files/invalid_permission | echo bye
===>Expeced return -- value: 0
bye

===>Got return -- value: 0

fdf
fdf
Redirection 41 ❌ echo hi >./test_files/invalid_permission | echo bye
===>Expeced return -- value: 0
bye

===>Got return -- value: 0

fdf
fdf
Redirection 42 ❌ echo hi >./test_files/invalid_permission >./outfiles/outfile01 | echo bye
===>Expeced return -- value: 0
bye

===>Got return -- value: 0

fdf
fdf
Redirection 43: ✅
fdf
fdf
Redirection 44: ✅
fdf
fdf
Redirection 45: ✅
fdf
fdf
Redirection 46 ❌ cat <"./test_files/infile" >./test_files/invalid_permission
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 47 ❌ cat >./test_files/invalid_permission <"./test_files/infile"
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 48 ❌ cat <missing >./outfiles/outfile01
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 49 ❌ cat >./outfiles/outfile01 <missing
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 50 ❌ cat <missing >./test_files/invalid_permission
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 51 ❌ cat >./test_files/invalid_permission <missing
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 52 ❌ cat >./outfiles/outfile01 <missing >./test_files/invalid_permission
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 53 ❌ ls >>./outfiles/outfile01
===>Expeced return -- value: 0

===>Got return -- value: 134

fdf
fdf
Redirection 54 ❌ ls >>      ./outfiles/outfile01
===>Expeced return -- value: 0

===>Got return -- value: 134

fdf
fdf
Redirection 55 ❌ ls >>./outfiles/outfile01 >./outfiles/outfile01
===>Expeced return -- value: 0

===>Got return -- value: 134

fdf
fdf
Redirection 56 ❌ ls >./outfiles/outfile01 >>./outfiles/outfile01
===>Expeced return -- value: 0

===>Got return -- value: 134

fdf
fdf
Redirection 57 ❌ ls >./outfiles/outfile01 >>./outfiles/outfile01 >./outfiles/outfile02
===>Expeced return -- value: 0

===>Got return -- value: 134

fdf
fdf
Redirection 58 ❌ ls >>./outfiles/outfile01 >>./outfiles/outfile02
===>Expeced return -- value: 0

===>Got return -- value: 134

fdf
fdf
Redirection 59 ❌ ls >>./test_files/invalid_permission
===>Expeced return -- value: 0

===>Got return -- value: 134

fdf
fdf
Redirection 60 ❌ ls >>./test_files/invalid_permission >>./outfiles/outfile01
===>Expeced return -- value: 0

===>Got return -- value: 134

fdf
fdf
Redirection 61 ❌ ls >>./outfiles/outfile01 >>./test_files/invalid_permission
===>Expeced return -- value: 0

===>Got return -- value: 134

fdf
fdf
Redirection 62 ❌ ls >./outfiles/outfile01 >>./test_files/invalid_permission >>./outfiles/outfile02
===>Expeced return -- value: 0

===>Got return -- value: 134

fdf
fdf
Redirection 63 ❌ ls <missing >>./test_files/invalid_permission >>./outfiles/outfile02
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 64 ❌ ls >>./test_files/invalid_permission >>./outfiles/outfile02 <missing
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 65 ❌ echo hi >>./outfiles/outfile01 | echo bye
===>Expeced return -- value: 0
bye

===>Got return -- value: 0

fdf
fdf
Redirection 66 ❌ echo hi >>./outfiles/outfile01 >>./outfiles/outfile02 | echo bye
===>Expeced return -- value: 0
bye

===>Got return -- value: 0

fdf
fdf
Redirection 67: ✅
fdf
fdf
Redirection 68: ✅
fdf
fdf
Redirection 69: ✅
fdf
fdf
Redirection 70 ❌ echo hi >>./test_files/invalid_permission | echo bye
===>Expeced return -- value: 0
bye

===>Got return -- value: 0

fdf
fdf
Redirection 71 ❌ echo hi >>./test_files/invalid_permission >./outfiles/outfile01 | echo bye
===>Expeced return -- value: 0
bye

===>Got return -- value: 0

fdf
fdf
Redirection 72: ✅
fdf
fdf
Redirection 73: ✅
fdf
fdf
Redirection 74 ❌ cat <minishell.h>./outfiles/outfile
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 75 ❌ cat <minishell.h|ls
===>Expeced return -- value: 0
=*
b
minishell
outfiles
test_files

===>Got return -- value: 134

fdf
fdf
Redirection 76 ❌ echo hello > $sdfsdf
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 77 ❌ echo hello >> $sdfsdf
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 78 ❌ echo hello < $sdfsdf
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 83 ❌ echo hello > $sdfsdf
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 84 ❌ < a > b
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 85 ❌ pwd |  ls > /dev/stdin
===>Expeced return -- value: 1

===>Got return -- value: 134

fdf
fdf
Redirection 86 ❌ ls > /dev/stdin | cat test_files/infile_big | head -n5
===>Expeced return -- value: 0

===>Got return -- value: 134

fdf
fdf
Redirection 87 ❌ echo hlelo |  ls > /dev/stdin
===>Expeced return -- value: 1

===>Got return -- value: 0

fdf
fdf
Redirection 88: ✅

█▀ █▄█ █▄░█ ▄▀█ ▀█▀ ▄▀█ ▀▄▀
▄█ ░█░ █░▀█ █▀█ ░█░ █▀█ █░█ 

fdf
fdf
empty command: ✅
fdf
fdf
just . ❌ .
===>Expeced return -- value: 127

===>Got return -- value: 0

fdf
fdf
just .. ❌ ..
===>Expeced return -- value: 127

===>Got return -- value: 0

fdf
fdf
Syntax 0 ❌ echo hello >      
===>Expeced return -- value: 2

===>Got return -- value: 0

fdf
fdf
Syntax 1 ❌ | echo oi
===>Expeced return -- value: 2

===>Got return -- value: 0

fdf
fdf
Syntax 2 ❌ |
===>Expeced return -- value: 2

===>Got return -- value: 0

fdf
fdf
Syntax 3 ❌ | |
===>Expeced return -- value: 2

===>Got return -- value: 0

fdf
fdf
Syntax 4 ❌ | $
===>Expeced return -- value: 2

===>Got return -- value: 0

fdf
fdf
Syntax 5 ❌ > > >> >>
===>Expeced return -- value: 2

===>Got return -- value: 0

fdf
fdf
Syntax 6 ❌ < <<
===>Expeced return -- value: 2

===>Got return -- value: 0

fdf
fdf
Syntax 7 ❌ cat    <| ls
===>Expeced return -- value: 2

===>Got return -- value: 134

fdf
fdf
Syntax 8 ❌ echo hi <
===>Expeced return -- value: 2

===>Got return -- value: 0

fdf
fdf
Syntax 9 ❌ > >>
===>Expeced return -- value: 2

===>Got return -- value: 0

fdf
fdf
Syntax 10 ❌ echo hi | < |
===>Expeced return -- value: 2

===>Got return -- value: 0

fdf
fdf
Syntax 11 ❌ echo hi |   |
===>Expeced return -- value: 2

===>Got return -- value: 0

fdf
fdf
Syntax 12 ❌ echo hi |  |
===>Expeced return -- value: 2

===>Got return -- value: 0

fdf
fdf
Syntax 13 ❌ echo hi |
===>Expeced return -- value: 2

===>Got return -- value: 0

fdf
fdf
Syntax 14 ❌ > |
===>Expeced return -- value: 2

===>Got return -- value: 0

fdf
fdf
Syntax 15 ❌ | >>
===>Expeced return -- value: 2

===>Got return -- value: 0

fdf
fdf
Syntax 16 ❌ <<
===>Expeced return -- value: 2

===>Got return -- value: 0

fdf
fdf
Syntax 17 ❌ >
===>Expeced return -- value: 2

===>Got return -- value: 0