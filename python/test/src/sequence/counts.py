import sys
import unittest

sys.path.append('./genesis_bindings')

from mylibgenesis.genesis.utils import *
from mylibgenesis.genesis.sequence import *

class CountsTest(unittest.TestCase):

	def test_Entropy(self):
		s0 = Sequence( "", "AAAA" )
		s1 = Sequence( "", "AAAC" )
		s2 = Sequence( "", "AACG" )
		s3 = Sequence( "", "ACGT" )

		c = SiteCounts( "ACGT", 4 )

		c.add_sequence( s0 )
		c.add_sequence( s1 )
		c.add_sequence( s2 )
		c.add_sequence( s3 )

		# ENTROPY-1
		if 0.0 		!= site_entropy( 	c, 0 ):
			print("Error at ENTROPY-1")
		# ENTROPY-2
		if 2.0 		!= site_information( 	c, 0 ):
			print("Error at ENTROPY-2")
		# ENTROPY-3
		if round(0.8112781,6) 	!= round(site_entropy( 		c, 1),6):
			print("Error at ENTROPY-3")
		# ENTROPY-4
		if round(1.1887219,6)	!= round(site_information(	c, 1),6):
			print("Error at ENTROPY-4")
		# ENTROPY-5
		if 1.5		!= site_entropy( 	c, 2 ):
			print("Error at ENTROPY-5")
		# ENTROPY-6
		if 0.5		!= site_information( 	c, 2 ):
			print("Error at ENTROPΥ-6")
		# ENTROPY-7
		if 2.0		!= site_entropy( 	c, 3 ):
			print("Error at ENTROPΥ-7")
		# ENTROPY-8
		if 0.0		!= site_information( 	c, 3 ):
			print("Error at ENTROPY-8")

		# ENTROPY-9
		if round(4.3112783,6)	!= round(absolute_entropy( c ),6):
			print("Error at ENTROPY-9")
		# ENTROPY-10
		if round(1.0778196,6)	!= round(average_entropy( c ),6):
		        print("Error at ENTROPY-10")

		# ENTROPY-11
		if "AAAA"	!= consensus_sequence_with_majorities( c ):
			print("Error at ENTROPY-11")

	def test_Consensus_Majority(self):
		sset = SequenceSet()
		PhylipReader().label_length( 10 ).read( from_file("./test/data/sequence/dna_5_42_s.phylip"), sset)

		counts = SiteCounts( "ACGT", 42 )
		counts.add_sequences( sset )

		# CONSENSUS_MAJORITY-1"
		if "AAACCCTGGCCGTTCAGGGTAAACCGTGGCCGGGCAGGGTAT" != consensus_sequence_with_majorities( counts ):
			print("Error at CONSENSUS_MAJORITY-1")

	def test_Consensus_Ambiguity(self):
		sset = SequenceSet()
		PhylipReader().label_length( 10 ).read( from_file("./test/data/sequence/dna_5_42_s.phylip"), sset)

		counts = SiteCounts( "ACGT", 42 )
		counts.add_sequences( sset )

		# CONSENSUS_AMBIGUITY-1
		if "AARCCYTGGCCGTTCAGGGTAAACCGTGGCCGGKCAGGGTAT" != consensus_sequence_with_ambiguities( counts, 1.0 ):
			print("Error at CONSENSUS_AMBIGUITY-1")
		# CONSENSUS_AMBIGUITY-2
		if "AARCCYTGGCCGTTCAGGGTAAACCGTGGCCGGKCAGGGTAT" != consensus_sequence_with_ambiguities( counts, 0.75 ):
			print("Error at CONSENSUS_AMBIGUITY-2")
		# CONSENSUS_AMBIGUITY-3
		if "AAVCC-TKGCMGTTMMGSKTRARCCNTGGCCGKDMMGSKTAW" != consensus_sequence_with_ambiguities( counts, 0.5 ):
			print("Error at CONSENSUS_AMBIGUITY-3")
		# CONSENSUS_AMBIGUITY-4
		if "AMVSB-KKGCMKKKMMGSKTRMRSSNDKGCMRKDMMVSKYAW" != consensus_sequence_with_ambiguities( counts, 0.0 ):
			print("Error at CONSENSUS_AMBIGUITY-4")

		counts_2 = SiteCounts( "ACGT", 5 )
		# CONSENSUS_AMBIGUITY-5
		if "-----" != consensus_sequence_with_ambiguities( counts_2, 1.0, True ):
			print("Error at CONSENSUS_AMBIGUITY-5")
		# CONSENSUS_AMBIGUITY-6
		if "-----" != consensus_sequence_with_ambiguities( counts_2, 0.0, True ):
			print("Error at CONSENSUS_AMBIGUITY-6")
		# CONSENSUS_AMBIGUITY-7
		if "-----" != consensus_sequence_with_ambiguities( counts_2, 1.0, False ):
			print("Error at CONSENSUS_AMBIGUITY-7")
		# CONSENSUS_AMBIGUITY-8
		if "-----" != consensus_sequence_with_ambiguities( counts_2, 0.0, False ):
			print("Error at CONSENSUS_AMBIGUITY-8")

		counts_2.add_sequence( "-ACGT" )
		# CONSENSUS_AMBIGUITY-9
		if "-ACGT" != consensus_sequence_with_ambiguities( counts_2, 1.0, True ):
			print("Error at CONSENSUS_AMBIGUITY-9")
		# CONSENSUS_AMBIGUITY-10
		if "-ACGT" != consensus_sequence_with_ambiguities( counts_2, 0.0, True ):
			print("Error at CONSENSUS_AMBIGUITY-10")
		# CONSENSUS_AMBIGUITY-11
		if "-ACGT" != consensus_sequence_with_ambiguities( counts_2, 1.0, False ):
			print("Error at CONSENSUS_AMBIGUITY-11")
		# CONSENSUS_AMBIGUITY-12
		if "-ACGT" != consensus_sequence_with_ambiguities( counts_2, 0.0, False ):
			print("Error at CONSENSUS_AMBIGUITY-12")

		counts_2.add_sequence( "-ACCT" )
		counts_2.add_sequence( "ACCT-" )
		# CONSENSUS_AMBIGUITY-12
		if "-ACBT" != consensus_sequence_with_ambiguities( counts_2, 1.0, True ):
			print("Error at CONSENSUS_AMBIGUITY-13")
		# CONSENSUS_AMBIGUITY-13
		if "-MCB-" != consensus_sequence_with_ambiguities( counts_2, 0.0, True ):
			print("Error at CONSENSUS_AMBIGUITY-14")
		# CONSENSUS_AMBIGUITY-14
		if "AACBT" != consensus_sequence_with_ambiguities( counts_2, 1.0, False ):
			print("Error at CONSENSUS_AMBIGUITY-15")
		# CONSENSUS_AMBIGUITY-15
		if "AMCBT" != consensus_sequence_with_ambiguities( counts_2, 0.0, False ):
			print("Error at CONSENSUS_AMBIGUITY-16")

	def test_Consensus_Threshold(self):
		sset = SequenceSet()
		PhylipReader().label_length( 10 ).read( from_file("./test/data/sequence/dna_5_42_s.phylip"), sset)

		counts = SiteCounts( "ACGT", 42 )
		counts.add_sequences( sset )

		# CONSENSUS_THRESHOLD-1
		if "AMVSB-KKGCMKKKMMGSKTRMRSSNDKGCMRKDMMVSKYAW" != consensus_sequence_with_threshold( counts, 1.0 ):
			print("Error at CONSENSUS_THRESHOLD-1")
		# CONSENSUS_THRESHOLD-2
		if "AARCSYTKGCMGTTMMGSKTRARCCVWGGCCGKKMMRSKTAW" != consensus_sequence_with_threshold( counts, 0.75 ):
			print("Error at CONSENSUS_THRESHOLD-2")
		# CONSENSUS_THRESHOLD-3
		if "AARCCYTGGCCGTTCAGGGTAAACCRTGGCCGGKCAGGGTAT" != consensus_sequence_with_threshold( counts, 0.5 ):
			print("Error at CONSENSUS_THRESHOLD-3")
		# CONSENSUS_THRESHOLD-4
		if "AAACCCTGGCCGTTCAGGGTAAACCGTGGCCGGGCAGGGTAT" != consensus_sequence_with_threshold( counts, 0.0 ):
			print("Error at CONSENSUS_THRESHOLD-4")

		counts_2 = SiteCounts( "ACGT", 5 )
		# CONSENSUS_THRESHOLD-5
		if "-----" != consensus_sequence_with_threshold( counts_2, 1.0, True ):
			print("Error at CONSENSUS_THRESHOLD-5")
		# CONSENSUS_THRESHOLD-6
		if "-----" != consensus_sequence_with_threshold( counts_2, 0.0, True ):
			print("Error at CONSENSUS_THRESHOLD-6")
		# CONSENSUS_THRESHOLD-7
		if "-----" != consensus_sequence_with_threshold( counts_2, 1.0, False ):
			print("Error at CONSENSUS_THRESHOLD-7")
		# CONSENSUS_THRESHOLD-8
		if "-----" != consensus_sequence_with_threshold( counts_2, 0.0, False ):
			print("Error at CONSENSUS_THRESHOLD-8")

		counts_2.add_sequence( "-ACGT" )
		# CONSENSUS_THRESHOLD-9
		if "-ACGT" != consensus_sequence_with_threshold( counts_2, 1.0, True ):
			print("Error at CONSENSUS_THRESHOLD-9")
		# CONSENSUS_THRESHOLD-10
		if "-ACGT" != consensus_sequence_with_threshold( counts_2, 0.0, True ):
			print("Error at CONSENSUS_THRESHOLD-10")
		# CONSENSUS_THRESHOLD-11
		if "-ACGT" != consensus_sequence_with_threshold( counts_2, 1.0, False ):
			print("Error at CONSENSUS_THRESHOLD-11")
		# CONSENSUS_THRESHOLD-12
		if "-ACGT" != consensus_sequence_with_threshold( counts_2, 0.0, False ):
			print("Error at CONSENSUS_THRESHOLD-12")

		counts_2.add_sequence( "-ACCT" )
		counts_2.add_sequence( "ACCT-" )
		# CONSENSUS_THRESHOLD-13
		if "-MCB-" != consensus_sequence_with_threshold( counts_2, 1.0, True ):
			print("Error at CONSENSUS_THRESHOLD-13")
		# CONSENSUS_THRESHOLD-14
		if "-ACCT" != consensus_sequence_with_threshold( counts_2, 0.0, True ):
			print("Error at CONSENSUS_THRESHOLD-14")
		# CONSENSUS_THRESHOLD-15
		if "AMCBT" != consensus_sequence_with_threshold( counts_2, 1.0, False ):
			print("Error at CONSENSUS_THRESHOLD-15")
		# CONSENSUS_THRESHOLD-16
		if "AACCT" != consensus_sequence_with_threshold( counts_2, 0.0, False ):
			print("Error at CONSENSUS_THRESHOLD-16")

	def test_Consensus_Cavener(self):
		sset = SequenceSet()
		PhylipReader().label_length( 10 ).read( from_file("./test/data/sequence/dna_5_42_s.phylip"), sset)

		counts = SiteCounts( "ACGT", 42 )
		counts.add_sequences( sset )

		#CONSENSUS_CAVENER-1
		if "AARCCYTKGCMGTTMMGSKTRARCCNTGGCCGKKMMGSKTAW" != consensus_sequence_cavener( counts, True ):
			print("Error at CONSENSUS_CAVENER-1")
		#CONSENSUS_CAVENER-2
		if "AARCCYTKGCMGTTMMGSKTRARCCNTGGCCGKKMMGSKTAW" != consensus_sequence_cavener( counts, False ):
			print("Error at CONSENSUS_CAVENER-2")

		counts_2 = SiteCounts( "ACGT", 5 )
		#CONSENSUS_CAVENER-3
		if "-----" != consensus_sequence_cavener( counts_2, True ):
			print("Error at CONSENSUS_CAVENER-3")
		#CONSENSUS_CAVENER-4
		if "-----" != consensus_sequence_cavener( counts_2, False ):
			print("Error at CONSENSUS_CAVENER-4")

		counts_2.add_sequence( "-ACGT" )
		#CONSENSUS_CAVENER-5
		if "-ACGT" != consensus_sequence_cavener( counts_2, True ):
			print("Error at CONSENSUS_CAVENER-5")
		#CONSENSUS_CAVENER-6
		if "-ACGT" != consensus_sequence_cavener( counts_2, False ):
			print("Error at CONSENSUS_CAVENER-6")

		counts_2.add_sequence( "-ACCT" )
		counts_2.add_sequence( "ACCT-" )
		#CONSENSUS_CAVENER-7
		if "-MCB-" != consensus_sequence_cavener( counts_2, True ):
			print("Error at CONSENSUS_CAVENER-7")
		#CONSENSUS_CAVENER-8
		if "AMCBT" != consensus_sequence_cavener( counts_2, False ):
			print("Error at CONSENSUS_CAVENER-8")

if __name__ == '__main__':
    unittest.main()
