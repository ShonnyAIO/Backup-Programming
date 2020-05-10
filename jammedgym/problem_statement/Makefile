fig.pdf: fig.tex
	xelatex fig.tex
	make clean

fig.tex: makefig.py
	python makefig.py

clean:
	rm -f fig.aux
	rm -f fig.log
	rm -f fig.tex
