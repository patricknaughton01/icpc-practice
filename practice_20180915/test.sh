for f in *.in; do
    echo "$f";
    cat "$f" | python3 ProblemA.py;
done
