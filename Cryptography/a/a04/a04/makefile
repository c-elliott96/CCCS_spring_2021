
pdf:
	pdflatex --shell-escape main.tex
	pdflatex --shell-escape main.tex
	make cleantmp
        
student:
	make pdf
	rm -rf student
	rm -f student.tar
	rm -f student.tar.gz
	mkdir student
	rsync -rv --exclude '*~' --exclude 'auto' --exclude 'student' . student
	tar -cvf student.tar student
	gzip student.tar

view:
	xdg-open main.pdf

v:
	xdg-open main.pdf
        
plain:
	setstyle.py main.tex --style=plain
	make

fancy:
	setstyle.py main.tex --style=fancy
	make

cleantmp:
	rm -rf abc.outut
	rm -rf 'main.log' 
	rm -rf 'main.aux'
	rm -rf 'main.toc'
	rm -rf 'main.out'
	rm -rf 'main.idx'
	rm -rf 'main.ilg'
	rm -rf 'texput.log'
	rm -rf 'shEsc.tmp'
	rm -rf 'main.vrb'
	rm -rf 'main.snm'
	rm -rf 'main.nav'
	rm -rf 'abc.output'
	rm -rf 'main.py.err'
	rm -rf 'main.py.out'
	rm -rf 'makefile.old'
	rm -rf 'auto'
	rm -rf 'desktop.ini'
	rm -rf 'main.py'
	find 'latex.py' -exec grep -q 'jobname="main"' '{}' \;  -delete

clean:
	rm -rf 'main.pdf'
	rm -rf student
	rm -f student.*
	make cleantmp
        
c:
	make clean
    
mail:
	sendgmail --attach=main.pdf

