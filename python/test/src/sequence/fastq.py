import sys
import unittest

sys.path.append('./genesis_bindings')

from mylibgenesis.genesis.utils import *
from mylibgenesis.genesis.sequence import *

class FastqTest(unittest.TestCase):

	def test_fastq_reader(self):
		infile =  "./test/data/sequence/wiki.fastq"
		sset = SequenceSet()
		FastqReader().read( from_file(infile), sset)

		if 2 != sset.size():
			print("Error at FASTQ_READER")
		if "GATTTGGGGTTCAAAGCAGTATCGATCAAATAGTAAATCCATTTGTTCAACTCACAGTTT" != sset[0].sites():
			print("Error at FASTQ_READER")
		if sset[0].size() != len(sset[0].phred_scores()):
			print("Error at FASTQ_READER")

		if 6 != sset[0].phred_scores()[1]:
			print("Error at FASTQ_READER")

		qual_0 = [
		     0,  6,  6,  9,  7,  7,  7,  7,  9,  9,  9, 10,  8,  8,  4,  4,  4, 10, 10,  8,
		     7,  4,  4,  4,  4,  8, 13, 16,  9,  9,  9, 12, 10,  9,  6,  6,  8,  8,  9,  9,
		    20, 20, 34, 34, 37, 29, 29, 29, 29, 29, 29, 34, 34, 34, 34, 34, 34, 34, 21, 20
		]
		qual_1 = [
		    68, 69, 66, 69, 69, 69, 69, 69, 66, 69, 68, 68, 69, 69, 69, 66, 69, 69, 69, 69,
		    69, 69, 67, 67, 69, 63, 69, 66, 68, 69, 60, 63, 60, 62, 33, 64, 62, 61, 62, 62,
		    58, 56, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 49, 51, 51, 59, 60, 60, 58, 60,
		    67, 67, 67, 67, 63, 67, 67, 67, 61, 67, 67, 67, 64, 67, 67, 61, 33, 33, 33, 33,
		    33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33
		]

		if qual_0 != sset[0].phred_scores():
			print("Error at FASTQ_READER")
		if qual_1 != sset[1].phred_scores():
			print("Error at FASTQ_READER")

	def test_fastq_encoding(self):
		infile = "./test/data/sequence/SP1.fq";

		enc = guess_fastq_quality_encoding( from_file( infile ));
		if QualityEncoding.kSanger != enc:
			print("Error at FASTQ_ENCODING")

	def test_fastq_input_iterator(self):
		infile = "./test/data/sequence/SP1.fq"

		cnt = 0
		fastq_input_iterator = FastqInputIterator( from_file( infile ))
		for it in fastq_input_iterator:
			cnt += 1

		if 250 != cnt:
			print("Error at FASTQ_INPUT_ITERATOR-1")

	def test_fastq_writer(self):
		infile = "./test/data/sequence/SP1.fq";
		sset = FastqReader().read( from_file( infile ))

		written = StringWrapper()
		FastqWriter().write( sset, to_string( written ))

		data = file_read( infile );
		if data != written.get():
			print("Error at FASTQ_WRITER-1")

	def test_fastq_output_iterator(self):
		infile = "./test/data/sequence/SP1.fq"
		sset = FastqReader().read( from_file( infile ))

		target = StringWrapper()
		out_it = FastqOutputIterator(to_string( target ))
		#for seq in sset:
		#    out_it << seq;

		#data = file_read( infile );
		#if data != target:
		#	print("Error at FASTQ_OUTPUT_ITERATOR-1")

if __name__ == '__main__':
    unittest.main()