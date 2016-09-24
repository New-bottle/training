while true; do
	python fuck.py > F.in
	< F.in ./Fstd > F.ans
	< F.in ./F > F.out
	if ! diff F.ans F.out; then
		echo "WA"
		exit
	else
		echo "AC"
	fi
done
