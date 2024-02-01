import sys
import unittest

sys.path.append('./genesis_bindings')

from mylibgenesis.genesis.utils import *
from mylibgenesis.genesis.sequence import *

class PhylipTest(unittest.TestCase):

	def test_phylip_reader_aainterleaved(self):

		infile = "./test/data/sequence/aa_3_384_i.phylip"
		sset = SequenceSet()
		PhylipReader().label_length( 10 ).mode( PhylipReader.Mode.kInterleaved ).valid_chars( amino_acid_codes_all() ).read( from_file(infile), sset)

		if 3 != sset.size():
			print("Error at PHYLIP_READER_AAINTERLEAVED-1")
		if 384 !=          sset[0].length():
			print("Error at PHYLIP_READER_AAINTERLEAVED-2")
		if "CATH_HUMAN" != sset[2].label():
			print("Error at PHYLIP_READER_AAINTERLEAVED-3")
		if "G-AVTPVKNQ" != sset[0].sites()[160:10+160]:
			print("Error at PHYLIP_READER_AAINTERLEAVED-4")		

	def test_phylip_reader_dnainterleaved(self):

		infile = "./test/data/sequence/dna_5_42_i.phylip"
		sset = SequenceSet()
		PhylipReader().label_length( 10 ).mode( PhylipReader.Mode.kInterleaved ).valid_chars( nucleic_acid_codes_all() ).read( from_file(infile), sset)

		if 5 != sset.size():
			print("Error at PHYLIP_READER_DNAINTERLEAVED-1")
		if 42 !=           sset[0].length():
			print("Error at PHYLIP_READER_DNAINTERLEAVED-2")
		if "Turkey" !=     sset[0].label():
			print("Error at PHYLIP_READER_DNAINTERLEAVED-3")
		if "AAGCTNGGGC" != sset[0].sites()[ 0: 10 ]:
			print("Error at PHYLIP_READER_DNAINTERLEAVED-4")

	def test_phylip_reader_aasequential(self):

		infile = "./test/data/sequence/aa_3_384_s.phylip"
		sset = SequenceSet()
		PhylipReader().label_length( 10 ).valid_chars( amino_acid_codes_all() ).read( from_file(infile), sset)

		if 3 != sset.size():
			print("Error at PHYLIP_READER_AASEQUENTIAL-1")
		if 384 !=          sset[0].length():
			print("Error at PHYLIP_READER_AASEQUENTIAL-2")
		if "CATH_HUMAN" != sset[2].label():
			print("Error at PHYLIP_READER_AASEQUENTIAL-3")
		if "G-AVTPVKNQ" != sset[0].sites()[160: 10+160 ]:
			print("Error at PHYLIP_READER_AASEQUENTIAL-4")

	def test_phylip_reader_dnasequential(self):

		infile = "./test/data/sequence/dna_5_42_s.phylip"
		sset = SequenceSet()
		PhylipReader().label_length( 10 ).valid_chars( nucleic_acid_codes_all() ).read( from_file(infile), sset)

		if 5 != sset.size():
			print("Error at PHYLIP_READER_DNASEQUENTIAL-1")
		if 42 !=           sset[0].length():
			print("Error at PHYLIP_READER_DNASEQUENTIAL-2")
		if "Salmo gair" != sset[1].label():
			print("Error at PHYLIP_READER_DNASEQUENTIAL-3")
		if "CGGGCACGGT" != sset[1].sites()[30: 10+30]:
			print("Error at PHYLIP_READER_DNASEQUENTIAL-4")

	def test_phylip_writer(self):

		infile = "./test/data/sequence/dna_5_42_s.phylip"
		sset = SequenceSet()
		PhylipReader().label_length( 10 ).valid_chars( nucleic_acid_codes_all() ).read( from_file(infile), sset)

		self.assertEqual( 5, sset.size())

		#target = StringTarget()
		#PhylipWriter().label_length(10).write( sset, to_string(target) )
		#if 6 != count_substring_occurrences( target.get(), "\n" ):
		#	print("Error at PHYLIP_WRITER-2")

if __name__ == '__main__':
    unittest.main()
