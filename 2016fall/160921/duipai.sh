while true; do
	python gen.py > guck.in
	< guck.in ./Gforce > g.ans
	< guck.in ./G > g.out
	if ! diff g.ans g.out ; then
		echo "WA"
		exit
	else
		echo "AC"
	fi
done
