import sys
import unittest

sys.path.append('./genesis_bindings')

from mylibgenesis.genesis.utils import *
from mylibgenesis.genesis.sequence import *

class SignaturesTest(unittest.TestCase):

	def test_kmer_list(self):
		for k in range(1,6):
			my_list = SignatureSpecifications( "ACGT", k ).kmer_list()

			# KMER_LIST-1
			self.assertEqual( int_pow( 4, k ) , len(my_list) )
			# KMER_LIST-2
			temp = "A" * k
			self.assertEqual( temp , my_list[0] )
			# KHMER_LIST-3
			temp = "T" * k
			self.assertEqual( temp , my_list[len(my_list)-1] )

	def test_kmer_counts(self):
		infile = "./test/data/sequence/dna_10.fasta"
		sset = SequenceSet()
		FastaReader().read( from_file(infile), sset)

		remove_all_gaps( sset )

		#KMER_COUNTS-1
		self.assertTrue( validate_chars( sset, nucleic_acid_codes_plain() ) )

		alphabet = "ACGT"

		for k in range(1,6):
			settings = SignatureSpecifications( alphabet, k )
			my_list = settings.kmer_list();

			for seq in sset:
				kmers = signature_counts( seq, settings )
				# KMER_COUNTS-2
				self.assertEqual( len(my_list) , len(kmers) )

				for i in range(0,len(kmers)):
					count = count_substring_occurrences( seq.sites(), my_list[i] )
					# KMER_COUNTS-3
					self.assertEqual( count , kmers[i] )

				sum = 0
				for i in range(0,len(kmers)):
					sum += kmers[i]
				# KMER_COUNTS-4
				self.assertEqual( (seq.size() - k + 1) , sum )

				sym_kmers = signature_symmetrized_counts( seq, settings )
				sum = 0
				for i in range(0,len(sym_kmers)):
					sum += sym_kmers[i]
				# KMER_COUNTS-5
				self.assertEqual( (seq.size() - k + 1) , sum )

	def test_signature_frequencies(self):
		infile = "./test/data/sequence/dna_10.fasta"
		sset = SequenceSet();
		FastaReader().read( from_file(infile), sset);

		# SIGNATURE_FREQUENCIES-1
		remove_all_gaps( sset );
		self.assertTrue( validate_chars( sset, nucleic_acid_codes_plain() ) )

		for k in range(1,6):
			settings = SignatureSpecifications( "ACGT", k )

			for seq in sset:
				# SIGNATURE_FREQUENCIES-1
				freqs = signature_frequencies( seq, settings )
				sum = 0.0
				for i in range(0,len(freqs)):
					sum += freqs[i]
				self.assertEqual( 1.0 , round(sum) )

				# SIGNATURE_FREQUENCIES-2
				sym_freqs = signature_symmetrized_frequencies( seq, settings );
				sym_sum = 0.0
				for i in range(0,len(sym_freqs)):
					sym_sum += sym_freqs[i]
				self.assertEqual( 1.0 , round(sym_sum) )

	def test_kmer_reverse_complements(self):
		for k in range(1,6):
			settings = SignatureSpecifications( "ACGT", k )
			my_list = settings.kmer_list()
			rc_map = settings.kmer_combined_reverse_complement_map()
			# KMER_REVERSE_COMPLEMENTS-1
			self.assertEqual( len(my_list) , len(rc_map) )

			revcom_size = settings.kmer_reverse_complement_list_size()

			for i in range(0,len(my_list)):
				rev = reverse_complement( my_list[i] )

				# KMER_REVERSE_COMPLEMENTS-2
				self.assertEqual( my_list[i] , reverse_complement(rev) )

				for j in range(0,len(my_list)):
					if my_list[j] == rev:
						break;

				# KMER_REVERSE_COMPLEMENTS-3
				if j >= len(my_list):
					print("Error at KMER_REVERSE_COMPLEMENTS-3")

				# KMER_REVERSE_COMPLEMENTS-4
				if rc_map[i] != rc_map[j]:
					print("Error at KMER_REVERSE_COMPLEMENTS-4")

				# KMER_REVERSE_COMPLEMENTS-5
				if rc_map[i] >= revcom_size:
					print("Error at KMER_REVERSE_COMPLEMENTS-5")

			rc_list = settings.kmer_reverse_complement_list()

			for i in range(0,len(rc_list)):
				rev = reverse_complement( rc_list[i] )
				if rev == rc_list[i]:
					continue
				for j in range(0,len(rc_list)):
					if rc_list[j] == rev:
						break;
				# KMMER_REVERSE_COMPLEMENTS-6
				if rc_list[j] != rc_list[len(rc_list)-1]:
					print("Error at KMER_REVERSE_COMPLEMENTS-6")

			rc_ids = settings.kmer_reverse_complement_indices()
			# KMER_REVERSE_COMPLEMENTS-7
			if len(rc_ids) != len(my_list):
				print("Error at KMER_REVERSE_COMPLEMENTS-7")
			for i in range(0,len(my_list)):
				# KMER_REVERSE_COMPLEMENTS-8
				if i != rc_ids[ rc_ids[i] ]:
					print("Error at KMER_REVERSE_COMPLEMENTS-8")
				rev = reverse_complement( my_list[i] )
				# KMER_REVERSE_COMPLEMENTS-9
				if rev != my_list[ rc_ids[i] ]:
					print("Error at KMER_REVERSE_COMPLEMENTS-9")

	def test_kmer_string_overlapping(self):
		seq = Sequence( "label", "AAAACCCCGGGGTTTT" )
		expected = [ "A A A A C C C C G G G G T T T T",
		        "AA AA AA AC CC CC CC CG GG GG GG GT TT TT TT",
		        "AAA AAA AAC ACC CCC CCC CCG CGG GGG GGG GGT GTT TTT TTT",
		        "AAAA AAAC AACC ACCC CCCC CCCG CCGG CGGG GGGG GGGT GGTT GTTT TTTT",
		        "AAAAC AAACC AACCC ACCCC CCCCG CCCGG CCGGG CGGGG GGGGT GGGTT GGTTT GTTTT" ]

		for k in range(1,6):
			settings = SignatureSpecifications( "ACGT", k )
			kmerstr  = kmer_string_overlapping( seq, settings )
			# KMER_STRING_OVERLAPPING-1
			if kmerstr != expected[k-1]:
				print("Error at KMER_STRING_OVERLAPPING-1")

		short_seq = Sequence( "label", "ACGT" )
		short_set = SignatureSpecifications( "ACGT", 5 );
		short_str  = kmer_string_overlapping( short_seq, short_set );
		# KMER_STRING_OVERLAPPING-2
		if short_str != "":
			print("Error at KMER_STRING_OVERLAPPING-2")

if __name__ == '__main__':
    unittest.main()
