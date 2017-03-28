#!/bin/bash
# -----------------------------------------------------------------------------
# Copy PNG-Files for all Info-Graphics here
# -----------------------------------------------------------------------------
# Note:
# This also recreates the collection of all graphics in single PDF file.

# Infographics used in this training:
#
OrderFile=order.txt

# Where PNGs and PDFs are stored:
#
InfoGraphics_PDF=../../../InfoGraphics/PDF
InfoGraphics_PNG=../../../InfoGraphics/PNG

# Where collection of all InfoGraphics go:
#
InfoGraphics_ALL=../PDF/InfoGraphics.pdf

# Check and change to directory containing this script
#
cd $(dirname $0) || {
	>&2 echo "$0: cannot change to script directory"
	exit 64
}
PROG=$(basename $0)

# Check existance and permissions of order file:
#
test -f "$OrderFile" -a -r "$OrderFile" || {
	>&2 echo "$PROG: order specification file does not exist: $OrderFile"
	exit 63
}

# Check tool dependency
#
type -t gs >/dev/null || {
	>&2 echo "$PROG: gs (ghostscript interpreter) not found"
	exit 62
}

# Check input directories
#
test -d $InfoGraphics_PNG || {
	>&2 echo "$PROG: input directory for png-files not found"
	exit 31
}
test -d $InfoGraphics_PDF || {
	>&2 echo "$PROG: input directory for pdf-files not found"
	exit 30
}

# Check output directories
#
test -d $(dirname $InfoGraphics_ALL) || {
	>&2 echo "$PROG: output directory for pdf-files not found"
	exit 29
}

# Process file list
sed -e	's/^[ \t]*//'	\
    -e	's/[ \t]*$//'	\
    -e	's/^#.*//'	\
    -e	'/^$/d'		\
	$OrderFile | (
	while read word line
	do
		png_cp=""
		png_in=""
		pdf_in=""

		case $word in
		(:*)	test -n "$group" && echo
			group=$line
			echo -n "$group "
			continue;;
		esac

		# check png input file
		png_in="$InfoGraphics_PNG/$word.png"
		test -f "$png_in" || {
			>&2 echo "$PROG: no such png input: $png_in"
			png_in=""
			echo -n "?"
		}
		#  check png destination
		png_cp="$word.png"
		test ! -f "$png_cp" -o -w "$png_cp" || {
			>&2 echo "$PROG: permission problem to create png copy: $png_cp"
			png_cp=""
			echo -n "-"
		}

		# check pdf input file
		pdf_in="$InfoGraphics_PDF/$word.pdf"
		test -f "$pdf_in" || {
			>&2 echo "$PROG: no such pdf input: $pdf_in"
			pdf_in=""
			echo -n "!"
		}

		# actually copy png file
		test -n "$png_in" -a -n "$png_cp" \
		     -a "$png_in" -nt "$png_cp" && {
			cp -a "$png_in" "$png_cp"
			echo -n "."
		}
		# add pdf file to list
		test -n "$pdf_in" && {
			all_pdf="$all_pdf $pdf_in"
			echo -n "+"
		}
	done

	# terminate last group
	test -n "$group" && echo

	# generate collected postscript
	echo "collecting into $InfoGraphics_ALL"
	gs -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=$InfoGraphics_ALL $all_pdf

)
