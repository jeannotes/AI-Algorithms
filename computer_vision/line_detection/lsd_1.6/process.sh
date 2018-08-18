echo $1

./lsd -P final.result.eps $1 final.result.txt
xdg-open final.result.eps