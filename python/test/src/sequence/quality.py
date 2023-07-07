import sys
import unittest

sys.path.append('./genesis_bindings')

from mylibgenesis.genesis.utils import *
from mylibgenesis.genesis.sequence import *

sanger = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHI"
illumina13 = "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefgh"
illumina15 = "BCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghi"
illumina18 = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJ"
solexa = ";<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefgh"

class PrintTest(unittest.TestCase):

	def test_quality_decoding_char(self):

		# QUALITY_DECODING_CHAR-1
		for i in range(0,len(sanger)):
			temp = [i]
			if temp != quality_decode_to_phred_score( sanger[i], QualityEncoding.kSanger):
				print("Error at QUALITY_DECODING_CHAR-1")
		# QUALITY_DECODING_CHAR-2
		for i in range(0,len(illumina13)):
			temp = [i]
			if temp != quality_decode_to_phred_score( illumina13[i], QualityEncoding.kIllumina13):
				print("Error at QUALITY_DECODING_CHAR-2")

		# QUALITY_DECODING_CHAR-3
		for i in range(0,len(illumina15)):
			temp = [i]
			temp2 = quality_decode_to_phred_score( illumina15[i], QualityEncoding.kIllumina15 )
			temp2 = temp2[0] - 2
			temp2 = [temp2]
			if temp != temp2:
				print("Error at QUALITY_DECODING_CHAR-3")
		# QUALITY_DECODING_CHAR-4
		for i in range(0,len(illumina18)):
			temp = [i]
			if temp != quality_decode_to_phred_score( illumina18[i], QualityEncoding.kIllumina18):
				print("Error at QUALITY_DECODING_CHAR-4")

		# QUALITY_DECODING_CHAR-5
		if [1] != quality_decode_to_phred_score( solexa[0], QualityEncoding.kSolexa ):
			print("Error at QUALITY_DECODING_CHAR-5")
		# QUALITY_DECODING_CHAR-6
		if [1] != quality_decode_to_phred_score( solexa[1], QualityEncoding.kSolexa ):
			print("Error at QUALITY_DECODING_CHAR-6")
		# QUALITY_DECODING_CHAR-7
		if [2] != quality_decode_to_phred_score( solexa[2], QualityEncoding.kSolexa ):
			print("Error at QUALITY_DECODING_CHAR-7")
		# QUALITY_DECODING_CHAR-8
		if [2] != quality_decode_to_phred_score( solexa[3], QualityEncoding.kSolexa ):
			print("Error at QUALITY_DECODING_CHAR-8")
		# QUALITY_DECODING_CHAR-9
		if [3] != quality_decode_to_phred_score( solexa[4], QualityEncoding.kSolexa ):
			print("Error at QUALITY_DECODING_CHAR-9")
		# QUALITY_DECODING_CHAR-10
		if [3] != quality_decode_to_phred_score( solexa[5], QualityEncoding.kSolexa ):
			print("Error at QUALITY_DECODING_CHAR-10")
		# QUALITY_DECODING_CHAR-11
		if [4] != quality_decode_to_phred_score( solexa[6], QualityEncoding.kSolexa ):
			print("Error at QUALITY_DECODING_CHAR-11")
		# QUALITY_DECODING_CHAR-12
		if [4] != quality_decode_to_phred_score( solexa[7], QualityEncoding.kSolexa ):
			print("Error at QUALITY_DECODING_CHAR-12")
		# QUALITY_DECODING_CHAR-13
		if [5] != quality_decode_to_phred_score( solexa[8], QualityEncoding.kSolexa ):
			print("Error at QUALITY_DECODING_CHAR-13")
		# QUALITY_DECODING_CHAR-14
		if [5] != quality_decode_to_phred_score( solexa[9], QualityEncoding.kSolexa ):
			print("Error at QUALITY_DECODING_CHAR-14")
		# QUALITY_DECODING_CHAR-15
		if [6] != quality_decode_to_phred_score( solexa[10], QualityEncoding.kSolexa ):
			print("Error at QUALITY_DECODING_CHAR-15")
		# QUALITY_DECODING_CHAR-16
		if [7] != quality_decode_to_phred_score( solexa[11], QualityEncoding.kSolexa ):
			print("Error at QUALITY_DECODING_CHAR-16")
		# QUALITY_DECODING_CHAR-17
		if [8] != quality_decode_to_phred_score( solexa[12], QualityEncoding.kSolexa ):
			print("Error at QUALITY_DECODING_CHAR-17")
		# QUALITY_DECODING_CHAR-18
		if [9] != quality_decode_to_phred_score( solexa[13], QualityEncoding.kSolexa ):
			print("Error at QUALITY_DECODING_CHAR-18")
		# QUALITY_DECODING_CHAR-19
		if [10] != quality_decode_to_phred_score( solexa[14], QualityEncoding.kSolexa ):
			print("Error at QUALITY_DECODING_CHAR-19")
		# QUALITY_DECODING_CHAR-20
		for i in range(15,len(solexa)):
			temp = [i]
			temp2 = quality_decode_to_phred_score( solexa[i], QualityEncoding.kSolexa )
			temp2 = temp2[0] + 5
			temp2 = [temp2]
			if [i] != temp2:
				print("Error at QUALITY_DECODING_CHAR-20")

	def test_quality_decoding_string(self):

		# QUALITY_DECODING_STRING-1
		sanger_v = list(range(0,len(sanger)))
		if sanger_v != quality_decode_to_phred_score( sanger, QualityEncoding.kSanger):
			print("Error at QUALITY_DECODING_STRING-1")

		# QUALITY_DECODING_STRING-2
		illumina13_v = list(range(0,len(illumina13)))
		if illumina13_v != quality_decode_to_phred_score( illumina13, QualityEncoding.kIllumina13):
			print("Error at QUALITY_DECODING_STRING-2")

		# QUALITY_DECODING_STRING-3
		illumina15_v = list(range(2,len(illumina15)+2))
		if illumina15_v != quality_decode_to_phred_score( illumina15, QualityEncoding.kIllumina15):
			print("Error at QUALITY_DECODING_STRING-3")

		# QUALITY_DECODING_STRING-4
		illumina18_v = list(range(0,len(illumina18)))
		if illumina18_v != quality_decode_to_phred_score( illumina18, QualityEncoding.kIllumina18 ):
			print("Error at QUALITY_DECODING_STRING-4")

		solexa_v = [None] * len(solexa)
		solexa_v[0] = 1;
		solexa_v[1] = 1;
		solexa_v[2] = 2;
		solexa_v[3] = 2;
		solexa_v[4] = 3;
		solexa_v[5] = 3;
		solexa_v[6] = 4;
		solexa_v[7] = 4;
		solexa_v[8] = 5;
		solexa_v[9] = 5;
		solexa_v[10] = 6;
		solexa_v[11] = 7;
		solexa_v[12] = 8;
		solexa_v[13] = 9;
		solexa_v[14] = 10;
		for i in range(15, len(solexa)):
			solexa_v[i] = i - 5
		# QUALITY_DECODING_STRING-5
		if solexa_v != quality_decode_to_phred_score( solexa, QualityEncoding.kSolexa ):
			print("Error at QUALITY_DECODING_STRING-5");

	def test_quality_encoding_string(self):

		# QUALITY_ENCODING_STRING-1
		scores = [1,5,10,20,50,90]
		if scores != quality_decode_to_phred_score( quality_encode_from_phred_score( scores )):
			print("Error at QUALITY_ENCODING_STRING-1")

		# QUALITY_ENCODING_STRING-2
		codes = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHI"
		if codes != quality_encode_from_phred_score( quality_decode_to_phred_score( codes )):
			print("Error at QUALITY_ENCODING_STRING-2")

	def test_quality_omputations(self):

		# QUALITY_COMPUTATIONS-1
		for i in range(-5,50):
			if i != error_probability_to_solexa_score( solexa_score_to_error_probability( i )):
				print("Error at QUALITY_COMPUTATIONS-1")

		# QUALITY_COMPUTATIONS-2
		for i in range(0,50):
			if i != error_probability_to_phred_score( phred_score_to_error_probability( i )):
				print("Error at QUALITY_COMPUTATIONS-2")

		for i in range(10, 50):
			# QUALITY_COMPUTATIONS-3
			if i != phred_score_to_solexa_score( solexa_score_to_phred_score( i )):
				print("Error at QUALITY_COMPUTATIONS-3")
			# QUALITY_COMPUTATIONS-4
			if i != solexa_score_to_phred_score( phred_score_to_solexa_score( i )):
				print("Error at QUALITY COMPUTATIONS-4")

		# QUALITY_COMPUTATIONS-5
		if 1 != solexa_score_to_phred_score( -5 ):
			print("Error at QUALITY_COMPUTATIONS-5")
		# QUALITY_COMPUTATIONS-6
		if 1 != solexa_score_to_phred_score( -4 ):
			print("Error at QUALITY_COMPUTATIONS-6")
		# QUALITY_COMPUTATIONS-7
		if 2 != solexa_score_to_phred_score( -3 ):
			print("Error at QUALITY_COMPUTATIONS-7")
		# QUALITY_COMPUTATIONS-8
		if 2 != solexa_score_to_phred_score( -2 ):
			print("Error at QUALITY_COMPUTATIONS-8")
		# QUALITY_COMPUTATIONS-9
		if 3 != solexa_score_to_phred_score( -1 ):
			print("Error at QUALITY_COMPUTATIONS-9")
		# QUALITY_COMPUTATIONS-10
		if 3 != solexa_score_to_phred_score( 0 ):
			print("Error at QUALITY_COMPUTATIONS-10")
		# QUALITY_COMPUTATIONS-11
		if 4 != solexa_score_to_phred_score( 1 ):
			print("Error at QUALITY_COMPUTATIONS-11")
		# QUALITY_COMPUTATIONS-12
		if 4 != solexa_score_to_phred_score( 2 ):
			print("Error at QUALITY_COMPUTATIONS-12")
		# QUALITY_COMPUTATIONS-13
		if 5 != solexa_score_to_phred_score( 3 ):
			print("Error at QUALITY_COMPUTATIONS-13")
		# QUALITY_COMPUTATIONS-14
		if 5 != solexa_score_to_phred_score( 4 ):
			print("Error at QUALITY_COMPUTATIONS-14")
		# QUALITY_COMPUTATIONS-15
		if 6 != solexa_score_to_phred_score( 5 ):
			print("Error at QUALITY_COMPUTATIONS-15")
		# QUALITY_COMPUTATIONS-16
		if 7 != solexa_score_to_phred_score( 6 ):
			print("Error at QUALITY_COMPUTATIONS-16")
		# QUALITY_COMPUTATIONS-17
		if 8 != solexa_score_to_phred_score( 7 ):
			print("Error at QUALITY_COMPUTATIONS-17")
		# QUALITY_COMPUTATIONS-18
		if 9 != solexa_score_to_phred_score( 8 ):
			print("Error at QUALITY_COMPUTATIONS-18")
		# QUALITY_COMPUTATIONS-19
		if 10 != solexa_score_to_phred_score( 9 ):
			print("Error at QUALITY_COMPUTATIONS-19")
		# QUALITY_COMPUTATIONS-20
		if 10 != solexa_score_to_phred_score( 10 ):
			print("Error at QUALITY_COMPUTATIONS-20")

		# QUALITY_COMPUTATIONS-21
		if -5 != phred_score_to_solexa_score( 0 ):
			print("Error at QUALITY_COMPUTATIONS-21")
		# QUALITY_COMPUTATIONS-22
		if -5 != phred_score_to_solexa_score( 1 ):
			print("Error at QUALITY_COMPUTATIONS-22")
		# QUALITY_COMPUTATIONS-23
		if -2 != phred_score_to_solexa_score( 2 ):
			print("Error at QUALITY_COMPUTATIONS-23")
		# QUALITY_COMPUTATIONS-24
		if 0 != phred_score_to_solexa_score( 3 ):
			print("Error at QUALITY_COMPUTATIONS-24")
		# QUALITY_COMPUTATIONS-25
		if 2 != phred_score_to_solexa_score( 4 ):
			print("Error at QUALITY_COMPUTATIONS-25")
		# QUALITY_COMPUTATIONS-26
		if 3 != phred_score_to_solexa_score( 5 ):
			print("Error at QUALITY_COMPUTATIONS-26")
		# QUALITY_COMPUTATIONS-27
		if 5 != phred_score_to_solexa_score( 6 ):
			print("Error at QUALITY_COMPUTATIONS-27")
		# QUALITY_COMPUTATIONS-28
		if 6 != phred_score_to_solexa_score( 7 ):
			print("Error at QUALITY_COMPUTATIONS-28")
		# QUALITY_COMPUTATIONS-29
		if 7 != phred_score_to_solexa_score( 8 ):
			print("Error at QUALITY_COMPUTATIONS-29")
		# QUALITY_COMPUTATIONS-30
		if 8 != phred_score_to_solexa_score( 9 ):
			print("Error at QUALITY_COMPUTATIONS-30")
		# QUALITY_COMPUTATIONS-31
		if 10 != phred_score_to_solexa_score( 10 ):
			print("Error at QUALITY_COMPUTATIONS-31")

	def test_quality_encoding_names(self):

		# QUALITY_ENCODING_NAMES-1
		if QualityEncoding.kSanger != guess_quality_encoding_from_name( quality_encoding_name( QualityEncoding.kSanger )):
			print("Error at QUALITY_ENCODING_NAMES-1")
		# QUALITY_ENCODING_NAMES-2
		if QualityEncoding.kIllumina13 != guess_quality_encoding_from_name( quality_encoding_name( QualityEncoding.kIllumina13 )):
			print("Error at QUALITY_ENCODING_NAMES-2")
		# QUALITY_ENCODING_NAMES-3
		if QualityEncoding.kIllumina15 != guess_quality_encoding_from_name( quality_encoding_name( QualityEncoding.kIllumina15 )):
			print("Error at QUALITY_ENCODING_NAMES-3")
		# QUALITY_ENCODING_NAMES-4
		if QualityEncoding.kIllumina18 != guess_quality_encoding_from_name( quality_encoding_name( QualityEncoding.kIllumina18 )):
			print("Error at QUALITY_ENCODING_NAMES-4")
		# QUALITY_ENCODING_NAMES-5
		if QualityEncoding.kSolexa != guess_quality_encoding_from_name( quality_encoding_name( QualityEncoding.kSolexa )):
			print("Error at QUALITY_ENCODING_NAMES-5")

		# QUALITY_ENCODING_NAMES-6
		if QualityEncoding.kIllumina18 != guess_quality_encoding_from_name( " Illumina." ):
			print("Error at QUALITY_ENCODING_NAMES-6")
		# QUALITY_ENCODING_NAMES-7
		exception_check = False
		try:
		    guess_quality_encoding_from_name( " IlluminiaX" )
		except RuntimeError:
		    exception_check = True
		if not exception_check:
		    print("Error at QUALITY_ENCODING_NAMES-7")
		# QUALITY_ENCODING_NAMES-8
		exception_check = False
		try:
		    guess_quality_encoding_from_name( "" )
		except RuntimeError:
		    exception_check = True
		if not exception_check:
		        print("Error at QUALITY_ENCODING_NAMES-8")

		# QUALITY_ENCODING_NAMES-9
		if  QualityEncoding.kSanger != guess_quality_encoding_from_name( "sanger" ):
			print("Error at QUALITY_ENCODING_NAMES-9")
		# QUALITY_ENCODING_NAMES-10
		if  QualityEncoding.kSolexa != guess_quality_encoding_from_name( "solexa" ):
			print("Error at QUALITY_ENCODING_NAMES-10")
		# QUALITY_ENCODING_NAMES-11
		if  QualityEncoding.kIllumina13 != guess_quality_encoding_from_name( "illumina-1.3" ):
			print("Error at QUALITY_ENCODING_NAMES-11")
		# QUALITY_ENCODING_NAMES-12
		if  QualityEncoding.kIllumina15 != guess_quality_encoding_from_name( "illumina-1.5" ):
			print("Error at QUALITY_ENCODING_NAMES-12")
		# QUALITY_ENCODING_NAMES-13
		if  QualityEncoding.kIllumina18 != guess_quality_encoding_from_name( "illumina-1.8" ):
			print("Error at QUALITY_ENCODING_NAMES-13")

if __name__ == '__main__':
    unittest.main()
