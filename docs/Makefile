SRC  =$(wildcard *.md)
HTML =$(patsubst %.md,%.html,$(SRC))

all: $(HTML)

%.html: %.md
	pandoc $< -o html/$@
	echo "<html>\n<head>\n<link rel=\"stylesheet\" href=\"style.css\">\n</head>\n<body>" | cat - html/$@ > temp
	echo "</body>\n</html>" >> temp
	mv temp html/$@

clean:
	rm html/*.html

.PHONY: clean
