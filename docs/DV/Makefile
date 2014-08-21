#include Makefile.inc

TARGET = AlkeGames_dvfinal

SOURCES = cover.tex presentation.tex description.tex target.tex control.tex similar.tex contact.tex logos.tex resources.tex

MAIN_FILE = dv.tex

LATEX = pdflatex

#DVI_FILE  = $(addsuffix .dvi, $(basename $(MAIN_FILE)))
#PS_FILE   = $(addsuffix .ps, $(basename $(MAIN_FILE)))
PDF_FILE  = $(addsuffix .pdf, $(basename $(MAIN_FILE)))
#BIB_FILE  = $(addsuffix .aux, $(basename $(MAIN_FILE)))

.PHONY: all

all: 
	@make $(TARGET).pdf

$(TARGET).pdf: $(MAIN_FILE) $(SOURCES)
	$(LATEX) $<
#	$(BIBTEX) $(BIB_FILE)
#	$(LATEX) $<
#	$(LATEX) $<
#	$(DVIPS) $(DVI_FILE)
#	$(PS2PDF) $(PS_FILE)
	@cp $(PDF_FILE) $@

clean:
	rm -f *~ $(PDF_FILE) *.dvi *.ps *.backup *.aux *.log *.nav *.out *.c.tex *.cpp.tex *.toc *.vrb *.dvi *.ps *.snm main.pdf *.bbl *.blg
