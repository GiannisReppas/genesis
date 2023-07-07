import numpy as np
import sys
import unittest

sys.path.append('./genesis_bindings')

from mylibgenesis.genesis.utils import *
from mylibgenesis.genesis.sequence import *

class LabelsTest(unittest.TestCase):

	def test_filter_by_label_test(self):
		infile = "./test/data/sequence/dna_10.fasta"
		sset = SequenceSet()
		FastaReader().read( from_file(infile), sset)

		# FILTER_BY_LABEL_LIST-1
		if 10 != sset.size():
			print("Error at FILTER_BY_LABEL_LIST-1")
		# FILTER_BY_LABEL_LIST-2
		if 4600 != total_length( sset ):
			print("Error at FILTER_BY_LABEL_LIST-2")

		good_labels = {
		    "Di106BGTue",
		    "Di145BGTue",
		    "Di307XishTrBotG",
		    "cs009BGTue",
		    "he005BGTue",
		    "he112BGTue",
		    "ne201NEStates"
		}

		bad_labels = {
		    "cs103MorArb",
		    "he111BGTue",
		    "ne203NEStates"
		}

		filter_by_label_list( sset, bad_labels )
		# FILTER_BY_LABEL_LIST-1
		if 7 != sset.size():
			print("Error at FILTER_BY_LABEL_LIST-1")
		# FILTER_BY_LABEL_LIST-2
		if good_labels != labels( sset ):
			print("Error at FILTER_BY_LABEL_LIST-2")

		filter_by_label_list( sset, good_labels );
		# FILTER_BY_LABEL_LIST-3
		if 0 != sset.size():
			print("Error at FILTER_BY_LABEL_LIST-3")
		# FILTER_BY_LABEL_LIST-4
		if not sset.empty():
			print("Error at FILTER_BY_LABEL_LIST-4")

	def test_guess_abundances(self):
		good = ( "abc", 123 )

		# GUESS_ABUNDANCES-1
		if good != guess_sequence_abundance( "abc_123" ):
			print("Error at GUESS_ABUNDANCES-1")
		# GUESS_ABUNDANCES-2
		if good != guess_sequence_abundance( "abc;size=123;" ):
			print("Error at GUESS_ABUNDANCES-2")
		# GUESS_ABUNDANCES-3
		if good != guess_sequence_abundance( "abc;size=123" ):
			print("Error at GUESS_ABUNDANCES-3")
		# GUESS_ABUNDANCES-4
		if good != guess_sequence_abundance( "abc;key=value;size=123;foo=bar;" ):
			print("Error at GUESS_ABUNDANCES-4")

		# GUESS_ABUNDANCES-5
		if ( "abc_size=123_", np.size(1) ) != guess_sequence_abundance( "abc_size=123_" ):
			print("Error at GUESS_ABUNDANCES-5")
		# GUESS_ABUNDANCES-6
		if ( "abcsize=123", np.size(1) ) != guess_sequence_abundance( "abcsize=123" ):
			print("Error at GUESS_ABUNDANCES-6")
		# GUESS_ABUNDANCES-7
		if ( "abc", np.size(1) ) != guess_sequence_abundance( "abc;size=123x" ):
			print("Error at GUESS_ABUNDANCES-7")

		# GUESS_ABUNDANCES-8
		if ( "abc_",       np.size(1) ) != guess_sequence_abundance( "abc_" ):
			print("Error at GUESS_ABUNDANCES-8")
		# GUESS_ABUNDANCES-9
		if ( "abc;size=",  np.size(1) ) != guess_sequence_abundance( "abc;size=" ):
			print("Error at GUESS_ABUNDANCES-9")
		# GUESS_ABUNDANCES-10
		if ( "abc_123x",   np.size(1) ) != guess_sequence_abundance( "abc_123x" ):
			print("Error at GUESS_ABUNDANCES-10")
		# GUESS_ABUNDANCES-11
		if ( "abc_x",      np.size(1) ) != guess_sequence_abundance( "abc_x" ):
			print("Error at GUESS_ABUNDANCES-11")
		# GUESS_ABUNDANCES-12
		if ( "abc", np.size(1) ) != guess_sequence_abundance( "abc;size=x" ):
			print("Error at GUESS_ABUNDANCES-12")

if __name__ == '__main__':
    unittest.main()
