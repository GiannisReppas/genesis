import sys
import unittest

sys.path.append('./genesis_bindings')

from mylibgenesis.genesis.utils import *
from mylibgenesis.genesis.sequence import *

class FastaTest(unittest.TestCase):

	def test_fasta_reader_validating(self):
		infile = "./test/data/sequence/dna_10.fasta"
		sset = SequenceSet()
		FastaReader().valid_chars( nucleic_acid_codes_all() ).read( from_file(infile), sset)

		if 10 != sset.size():
			print("Error at FASTA_READER_VALIDATING-1")
		if 460 !=                    sset[0].length():
			print("Error at FASTA_READER_VALIDATING-2")
		if "Di106BGTue" !=           sset[0].label():
			print("Error at FASTA_READER_VALIDATING-3")
		if "TCGAAACCTGC------CTA" != sset[0].sites()[0:20]:
			print("Error at FASTA_READER_VALIDATING-4")

	def test_reading_loop(self):
		infile = "./test/data/sequence/dna_10.fasta"
		fasta_input_iterator = FastaInputIterator( from_file( infile ))

		len = 0
		cnt = 0
		for seq in fasta_input_iterator:

			if cnt == 0:
				if "Di106BGTue" != seq.label():
					print("Error at READING_LOOP-1")

			if cnt == 9:
				if "GTCGTTCT" != seq.sites()[387:387+8]:
					print("Error at READING_LOOP-2")

			len = max( len, seq.length() )

			cnt += 1

		# no need to bind operator bool()
		#if fasta_input_iterator == False:
		#	print("Error at READING_LOOP-3")
		if 460 != len:
			print("Error at READING_LOOP-4")
		if 10 != cnt:
			print("Error at READING_LOOP-5")

	def test_fasta_compressed(self):
		infile = "./test/data/sequence/dna_10.fasta.gz";
		cit = InputStream( GzipInputSource(FileInputSource( infile )) )

		sset = SequenceSet()
		FastaReader().parse_document( cit, sset )

		if 10 != sset.size():
			print("Error at FASTA_COMPRESSED-1")
		if 460 !=                    sset[0].length():
			print("Error at FASTA_COMPRESSED-2")
		if "Di106BGTue" !=           sset[0].label():
			print("Error at FASTA_COMPRESSED-3")
		if "TCGAAACCTGC------CTA" != sset[0].sites()[0:20]:
			print("Error at FASTA_COMPRESSED-4")

	def test_fasta_gzip(self):
		infile = "./test/data/sequence/dna_10.fasta.gz"

		sset = FastaReader().read( from_file( infile ))

		if 10 != sset.size():
			print("Error at FASTA_GZIP-1")
		if 460 !=                    sset[0].length():
			print("Error at FASTA_GZIP-2")
		if "Di106BGTue" !=           sset[0].label():
			print("Error at FASTA_GZIP-3")
		if "TCGAAACCTGC------CTA" != sset[0].sites()[0:20]:
			print("Error at FASTA_GZIP-4")

	def test_fasta_writer(self):
		infile = "./test/data/sequence/dna_10.fasta"
		sset = SequenceSet()
		FastaReader().valid_chars( nucleic_acid_codes_all() ).read( from_file(infile), sset)

		if 10 != sset.size():
			print("Error at FASTA_WRITER-1")

		target = StringTarget()
		FastaWriter().line_length(50).write( sset, to_string( target ))
		read_again = file_read( infile )
		if target.get() == "":
			print("Error at FASTA_WRITER-2")
		if read_again != target.get():
			print("Error at FASTA_WRITER-3")

	def test_fasta_output_iterator(self):
		infile = "./test/data/sequence/dna_10.fasta"
		sset = FastaReader().read( from_file( infile ))

		target = StringTarget()
		out_it = FastaOutputIterator( to_string(target))

		print(target.get())

		out_it.writer().line_length( 50 );
		for seq in sset:
			out_it << seq;

		data = file_read( infile );
		if data != target.get():
			print("Error at FASTA_OUTPUT_ITERATOR-1")

if __name__ == '__main__':
    unittest.main()
