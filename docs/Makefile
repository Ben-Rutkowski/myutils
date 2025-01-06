SRC  =$(wildcard *.md)
HTML =$(patsubst %.md,%.html,$(SRC))

all: $(HTML)

%.html: %.md
	echo "<html>\n<head>\n<link rel=\"stylesheet\" href=\"style.css\">\n</head>\n<body>" > html/$@
	markdown $< >> html/$@
	echo "</body>\n</html>" >> html/$@

clean:
	rm html/*.html

.PHONY: clean
