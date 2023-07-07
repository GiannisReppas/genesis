import sys
import unittest

sys.path.append('./genesis_bindings')

from mylibgenesis.genesis.utils import *
from mylibgenesis.genesis.population import *

class BedReader(unittest.TestCase):

	def test_Read1(self):

		infile = "test/data/population/wiki1.bed3"

		reader = BedReader()
		regions = reader.read_as_genome_region_list( from_file( infile ))
		self.assertEqual( 3, regions.total_region_count() )
		self.assertFalse( regions.is_covered( "chr7", 127471196 ))
		self.assertTrue(  regions.is_covered( "chr7", 127471197 ))
		self.assertTrue(  regions.is_covered( "chr7", 127472363 ))
		self.assertFalse( regions.is_covered( "chr7", 127472364 ))
		self.assertTrue(  regions.is_covered( "chr7", 127472365 ))
		self.assertTrue(  regions.is_covered( "chr7", 127473530 ))
		self.assertFalse( regions.is_covered( "chr7", 127473531 ))
		self.assertTrue(  regions.is_covered( "chr7", 127473532 ))
		self.assertTrue(  regions.is_covered( "chr7", 127474697 ))
		self.assertFalse( regions.is_covered( "chr7", 127474698 ))

if __name__ == '__main__':
	unittest.main()
