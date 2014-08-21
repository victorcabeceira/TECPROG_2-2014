#include Makefile.inc

TARGET = AlkeGames_GDD

SOURCES = cover.tex concept.tex story.tex revision_table.tex beat_charts.tex control.tex endpage.tex

MAIN_FILE = gdd.tex

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
