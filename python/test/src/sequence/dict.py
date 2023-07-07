import sys
import unittest

sys.path.append('./genesis_bindings')

from mylibgenesis.genesis.utils import *
from mylibgenesis.genesis.sequence import *

class DictTest(unittest.TestCase):

	def tair10_dict_file_test( self, dict ):
		if              7 != dict.size():
			print("Error at test_tair10_dict_file-1")
		if            "1" != dict[0].name:
			print("Error at test_tair10_dict_file-2")
		if       30427671 != dict[0].length:
			print("Error at test_tair10_dict_file-3")
		if            "2" != dict[1].name:
			print("Error at test_tair10_dict_file-4")
		if       19698289 != dict[1].length:
			print("Error at test_tair10_dict_file-5")
		if            "3" != dict[2].name:
			print("Error at test_tair10_dict_file-6")
		if       23459830 != dict[2].length:
			print("Error at test_tair10_dict_file-7")
		if            "4" != dict[3].name:
			print("Error at test_tair10_dict_file-8")
		if       18585056 != dict[3].length:
			print("Error at test_tair10_dict_file-9")
		if            "5" != dict[4].name:
			print("Error at test_tair10_dict_file-10")
		if       26975502 != dict[4].length:
			print("Error at test_tair10_dict_file-11")
		if "mitochondria" != dict[5].name:
			print("Error at test_tair10_dict_file-12")
		if         366924 != dict[5].length:
			print("Error at test_tair10_dict_file-13")
		if  "chloroplast" != dict[6].name:
			print("Error at test_tair10_dict_file-14")
		if         154478 != dict[6].length:
			print("Error at test_tair10_dict_file-15")

		if    dict.end() == dict.find( "1" ):
			print("Error at test_tair10_dict_file-16")
		if    dict.end() != dict.find( "X" ):
			print("Error at test_tair10_dict_file-17")
		if not dict.contains( "1" ):
			print("Error at test_tair10_dict_file-18A")
		if "1" not in dict:
			print("Error at test_tair10_dict_file-18B")
		if dict.contains( "X" ):
			print("Error at test_tair10_dict_file-19")

	def test_dict_reader(self):
		infile = "./test/data/sequence/TAIR10_chr_all.dict"
		dict = read_sequence_dict( from_file( infile ))
		self.tair10_dict_file_test( dict )

	def test_fai_reader(self):
		infile = "./test/data/sequence/TAIR10_chr_all.fa.fai"
		dict = read_sequence_fai( from_file( infile ))
		self.tair10_dict_file_test( dict )

	def test_fasta_reader(self):
		infile = "./test/data/sequence/dna_10.fasta"
		dict = FastaReader().read_dict( from_file( infile ))

		# FASTA_READER-1
		if           10 != dict.size():
			print("Error at FASTA_READER-1")
		# FASTA_READER-2
		if "Di106BGTue" != dict[0].name:
			print("Error at FASTA_READER-2")
		# FASTA_READER-3
		if          460 != dict[0].length:
			print("Error at FASTA_READER-3")

	def test_fasta_convert(self):
		infile = "./test/data/sequence/dna_10.fasta"
		seqs = FastaReader().read(from_file( infile ))
		dict = sequence_set_to_dict( seqs )

		# FASTA_CONVERT-1
		if           10 != dict.size():
			print("Error at FASTA_CONVERT-1")
		# FASTA_CONVERT-2
		if "Di106BGTue" != dict[0].name:
			print("Error at FASTA_CONVERT-2")
		# FASTA_CONVERT-3
		if          460 != dict[0].length:
			print("Error at FASTA_CONVERT-3")
		# FASTA_CONVERT-4
		if not verify( dict, seqs, False ):
			print("Error at FASTA_CONVERT-4")
		# FASTA_CONVERT-5
		if not verify( dict, seqs, True ):
			print("Error at FASTA_CONVERT-5")

if __name__ == '__main__':
    unittest.main()