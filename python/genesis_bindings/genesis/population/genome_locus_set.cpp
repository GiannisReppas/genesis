#include <functional>
#include <genesis/population/formats/bed_reader.hpp>
#include <genesis/population/genome_locus.hpp>
#include <genesis/population/genome_locus_set.hpp>
#include <genesis/population/genome_region.hpp>
#include <genesis/utils/containers/interval_tree.hpp>
#include <genesis/utils/containers/interval_tree/interval.hpp>
#include <genesis/utils/io/base_input_source.hpp>
#include <genesis/utils/math/bitvector.hpp>
#include <iterator>
#include <map>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <utility>
#include <vector>

#include <functional>
#include <pybind11/pybind11.h>
#include <string>
#include <pybind11/functional.h>
#include <../python/custom_bindings/extensions/matrix.hpp>
#include <genesis/utils/tools/color/functions.hpp>
#include <../python/custom_bindings/extensions/bitvector.hpp>
#include <../python/custom_bindings/extensions/range.hpp>
#include <../python/custom_bindings/extensions/quality.hpp>
#include <../python/custom_bindings/extensions/sequence_set.hpp>
#include <../python/custom_bindings/extensions/sequence_dict.hpp>
#include <../python/custom_bindings/extensions/fasta_input_iterator.hpp>
#include <../python/custom_bindings/extensions/fastq_input_iterator.hpp>
#include <../python/custom_bindings/extensions/fasta_output_iterator.hpp>
#include <../python/custom_bindings/extensions/taxopath.hpp>
#include <../python/custom_bindings/extensions/functions_taxonomy.hpp>
#include <../python/custom_bindings/extensions/common_node_data.hpp>
#include <../python/custom_bindings/extensions/tree.hpp>
#include <../python/custom_bindings/extensions/functions_tree.hpp>
#include <genesis/population/genome_region_list.hpp>
#include <pybind11/stl.h>


#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

void bind_genesis_population_genome_locus_set(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // genesis::population::GenomeLocusSet file:genesis/population/genome_locus_set.hpp line:74
		pybind11::class_<genesis::population::GenomeLocusSet, std::shared_ptr<genesis::population::GenomeLocusSet>> cl(M("genesis::population"), "GenomeLocusSet", "List of positions/coordinates in a genome, for each chromosome.\n\n The data structure stores a list of genome positions/coordinates, and allows fast querying,\n that is, whether a certain position on a chromosome is stored here. Internally, we use a\n \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		cl.def( pybind11::init( [](){ return new genesis::population::GenomeLocusSet(); } ) );
		cl.def( pybind11::init( [](genesis::population::GenomeLocusSet const &o){ return new genesis::population::GenomeLocusSet(o); } ) );
		cl.def("assign", (class genesis::population::GenomeLocusSet & (genesis::population::GenomeLocusSet::*)(const class genesis::population::GenomeLocusSet &)) &genesis::population::GenomeLocusSet::operator=, "C++: genesis::population::GenomeLocusSet::operator=(const class genesis::population::GenomeLocusSet &) --> class genesis::population::GenomeLocusSet &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("add", (void (genesis::population::GenomeLocusSet::*)(const std::string &)) &genesis::population::GenomeLocusSet::add, "Add a whole chromosome to the list, so that all its positions are considered to be\n covered.\n\nC++: genesis::population::GenomeLocusSet::add(const std::string &) --> void", pybind11::arg("chromosome"));
		cl.def("add", (void (genesis::population::GenomeLocusSet::*)(const std::string &, unsigned long)) &genesis::population::GenomeLocusSet::add, "Add a single locus (position, coordinate) to the list.\n\nC++: genesis::population::GenomeLocusSet::add(const std::string &, unsigned long) --> void", pybind11::arg("chromosome"), pybind11::arg("position"));
		cl.def("add", (void (genesis::population::GenomeLocusSet::*)(const std::string &, unsigned long, unsigned long)) &genesis::population::GenomeLocusSet::add, "Add a region to the list, given its chromosome, and  and  positions.\n\n All positions between  and  are set.\n The  cannot be empty, and we expect  <  (or both equal to 0, for\n the special case denoting that the whole chromosome is to be considered covered).\n Both  and  are 1-based, and inclusive, that is, the interval between them is\n closed.\n\nC++: genesis::population::GenomeLocusSet::add(const std::string &, unsigned long, unsigned long) --> void", pybind11::arg("chromosome"), pybind11::arg("start"), pybind11::arg("end"));
		cl.def("add", (void (genesis::population::GenomeLocusSet::*)(const struct genesis::population::GenomeLocus &)) &genesis::population::GenomeLocusSet::add, "Add a single GenomeLocus, that is, an interval covering one position on a chromosome.\n\nC++: genesis::population::GenomeLocusSet::add(const struct genesis::population::GenomeLocus &) --> void", pybind11::arg("locus"));
		cl.def("add", (void (genesis::population::GenomeLocusSet::*)(const struct genesis::population::GenomeLocus &, const struct genesis::population::GenomeLocus &)) &genesis::population::GenomeLocusSet::add, "Add an interval between two \n\n\nC++: genesis::population::GenomeLocusSet::add(const struct genesis::population::GenomeLocus &, const struct genesis::population::GenomeLocus &) --> void", pybind11::arg("start"), pybind11::arg("end"));
		cl.def("add", (void (genesis::population::GenomeLocusSet::*)(const struct genesis::population::GenomeRegion &)) &genesis::population::GenomeLocusSet::add, "Add a GenomeRegion to the list.\n\n This function ensures that regions are valid (`start < end`).\n\nC++: genesis::population::GenomeLocusSet::add(const struct genesis::population::GenomeRegion &) --> void", pybind11::arg("region"));
		cl.def("add", (void (genesis::population::GenomeLocusSet::*)(const class genesis::population::GenomeRegionList &)) &genesis::population::GenomeLocusSet::add, "Add a complete GenomeRegionList to this list.\n\nC++: genesis::population::GenomeLocusSet::add(const class genesis::population::GenomeRegionList &) --> void", pybind11::arg("list"));
		cl.def("add", (void (genesis::population::GenomeLocusSet::*)(const std::string &, const class genesis::utils::Bitvector &)) &genesis::population::GenomeLocusSet::add, "Add a chromosome to the list, given the full Bitvector representation of loci.\n\n This assumes that the data of the Bitvector has been assembled according to the\n specifications of this class, i.e., respecting the special role of the 0th bit.\n\nC++: genesis::population::GenomeLocusSet::add(const std::string &, const class genesis::utils::Bitvector &) --> void", pybind11::arg("chromosome"), pybind11::arg("values"));
		cl.def("clear", (void (genesis::population::GenomeLocusSet::*)()) &genesis::population::GenomeLocusSet::clear, "Remove all stored regions from all chromosomes.\n\nC++: genesis::population::GenomeLocusSet::clear() --> void");
		cl.def("clear", (void (genesis::population::GenomeLocusSet::*)(const std::string &)) &genesis::population::GenomeLocusSet::clear, "Remove the regions of the specified \n     \n\nC++: genesis::population::GenomeLocusSet::clear(const std::string &) --> void", pybind11::arg("chromosome"));
		cl.def("set_intersect", (void (genesis::population::GenomeLocusSet::*)(const class genesis::population::GenomeLocusSet &)) &genesis::population::GenomeLocusSet::set_intersect, "Compute the intersection with another GenomeLocusSet \n\n Any chromosomes that end up having no positions covered are removed.\n\nC++: genesis::population::GenomeLocusSet::set_intersect(const class genesis::population::GenomeLocusSet &) --> void", pybind11::arg("rhs"));
		cl.def("set_union", (void (genesis::population::GenomeLocusSet::*)(const class genesis::population::GenomeLocusSet &)) &genesis::population::GenomeLocusSet::set_union, "Compute the union with another GenomeLocusSet \n     \n\nC++: genesis::population::GenomeLocusSet::set_union(const class genesis::population::GenomeLocusSet &) --> void", pybind11::arg("rhs"));
		cl.def("is_covered", (bool (genesis::population::GenomeLocusSet::*)(const std::string &, unsigned long) const) &genesis::population::GenomeLocusSet::is_covered, "Return whether a given position on a chromosome is part of any of the regions stored.\n\n Note that  is 1-based.\n\nC++: genesis::population::GenomeLocusSet::is_covered(const std::string &, unsigned long) const --> bool", pybind11::arg("chromosome"), pybind11::arg("position"));
		cl.def("is_covered", (bool (genesis::population::GenomeLocusSet::*)(const std::string &) const) &genesis::population::GenomeLocusSet::is_covered, "Return whether a whole chromosome is covered.\n\nC++: genesis::population::GenomeLocusSet::is_covered(const std::string &) const --> bool", pybind11::arg("chromosome"));
		cl.def("empty", (bool (genesis::population::GenomeLocusSet::*)() const) &genesis::population::GenomeLocusSet::empty, "Return whether there are chromosomes with positions stored.\n\nC++: genesis::population::GenomeLocusSet::empty() const --> bool");
		cl.def("chromosome_count", (unsigned long (genesis::population::GenomeLocusSet::*)() const) &genesis::population::GenomeLocusSet::chromosome_count, "Return the number of chromosomes for which there are positions stored.\n\nC++: genesis::population::GenomeLocusSet::chromosome_count() const --> unsigned long");
		cl.def("chromosome_names", (class std::vector<std::string, class std::allocator<std::string > > (genesis::population::GenomeLocusSet::*)() const) &genesis::population::GenomeLocusSet::chromosome_names, "Get a list of all stored chromosome names.\n\nC++: genesis::population::GenomeLocusSet::chromosome_names() const --> class std::vector<std::string, class std::allocator<std::string > >");
		cl.def("has_chromosome", (bool (genesis::population::GenomeLocusSet::*)(const std::string &) const) &genesis::population::GenomeLocusSet::has_chromosome, "Return whether a chromosome is stored.\n\nC++: genesis::population::GenomeLocusSet::has_chromosome(const std::string &) const --> bool", pybind11::arg("chromosome"));
		cl.def("chromosome_positions", (class genesis::utils::Bitvector & (genesis::population::GenomeLocusSet::*)(const std::string &)) &genesis::population::GenomeLocusSet::chromosome_positions, "For a given chromosome, return the\n \n\n\n\n\n\n\n\nC++: genesis::population::GenomeLocusSet::chromosome_positions(const std::string &) --> class genesis::utils::Bitvector &", pybind11::return_value_policy::reference_internal, pybind11::arg("chromosome"));
	}
	{ // genesis::population::BedReader file:genesis/population/formats/bed_reader.hpp line:91
		pybind11::class_<genesis::population::BedReader, std::shared_ptr<genesis::population::BedReader>> cl(M("genesis::population"), "BedReader", "Reader for BED (Browser Extensible Data) files.\n\n We follow the definition by https://en.wikipedia.org/wiki/BED_(file_format), which itself is\n based on the UCSC Genome Browser definition of the BED format:\n\n  Column number | Title        | Definition\n  ------------: | :----------- | :---------\n  1             | chrom        | Chromosome (e.g. chr3, chrY, chr2_random) or scaffold (e.g. scaffold10671) name\n  2             | chromStart   | Start coordinate on the chromosome or scaffold for the sequence considered (the first base on the chromosome is numbered 0 in the file format - we here however use 1-based coordinates)\n  3             | chromEnd     | End coordinate on the chromosome or scaffold for the sequence considered. This position is non-inclusive, unlike chromStart.\n  4             | name         | Name of the line in the BED file\n  5             | score        | Score between 0 and 1000\n  6             | strand       | DNA strand orientation (positive [\"+\"] or negative [\"-\"] or \".\" if no strand)\n  7             | thickStart   | Starting coordinate from which the annotation is displayed in a thicker way on a graphical representation (e.g.: the start codon of a gene)\n  8             | thickEnd     | End coordinates from which the annotation is no longer displayed in a thicker way on a graphical representation (e.g.: the stop codon of a gene)\n  9             | itemRgb      | RGB value in the form R,G,B (e.g. 255,0,0) determining the display color of the annotation contained in the BED file\n  10            | blockCount   | Number of blocks (e.g. exons) on the line of the BED file\n  11            | blockSizes   | List of values separated by commas corresponding to the size of the blocks (the number of values must correspond to that of the \"blockCount\")\n  12            | blockStarts  | List of values separated by commas corresponding to the starting coordinates of the blocks, coordinates calculated relative to those present in the chromStart column (the number of values must correspond to that of the \"blockCount\")\n\n The reader offers to parse every line or the whole file into a Feature format that contains the\n above columns (as far as present in the file), or to read into a GenomeRegionList structure\n instead, in which case only the genome coordinates (chromosome and start and end positions) are\n used. The input needs to have a consistent number of columns, but only the first three are\n mandatory. They all must be in the above order, and if later (more towards the end of the line)\n columns are needed, all previous ones need to be filled as well.\n Any additional columns after these 12 are also read by our parser, but simply ignored.\n\n Note that the BED format internally uses 0-based half-open intervals. That is, the start and end\n coordinates `chromStart = 0` and `chromEnd = 100` define a region starting at the first base,\n with a length of 100. We here however use 1-based closed intervals, and hence store the same\n region as `1` and `100`, both in the Feature struct and in the GenomeRegionList.\n\n Furthermore, any lines starting with `browser`, `track`, or `#` are read, but currently\n ignored. We are not quite sure if such lines are allowed in the middle of BED files by the\n inofficial standard, hence we here also allow that. The obvious downside of this being the BED\n specification is that chromosome names \"browser\" and \"track\" cannot be used.");
		cl.def( pybind11::init( [](){ return new genesis::population::BedReader(); } ) );
		cl.def( pybind11::init( [](genesis::population::BedReader const &o){ return new genesis::population::BedReader(o); } ) );
		cl.def("assign", (class genesis::population::BedReader & (genesis::population::BedReader::*)(const class genesis::population::BedReader &)) &genesis::population::BedReader::operator=, "C++: genesis::population::BedReader::operator=(const class genesis::population::BedReader &) --> class genesis::population::BedReader &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("read", (class std::vector<struct genesis::population::BedReader::Feature, class std::allocator<struct genesis::population::BedReader::Feature> > (genesis::population::BedReader::*)(class std::shared_ptr<class genesis::utils::BaseInputSource>) const) &genesis::population::BedReader::read, "Read a BED input source, and return its content as a list of Feature structs.\n\nC++: genesis::population::BedReader::read(class std::shared_ptr<class genesis::utils::BaseInputSource>) const --> class std::vector<struct genesis::population::BedReader::Feature, class std::allocator<struct genesis::population::BedReader::Feature> >", pybind11::arg("source"));
		cl.def("read_as_genome_locus_set", (class genesis::population::GenomeLocusSet (genesis::population::BedReader::*)(class std::shared_ptr<class genesis::utils::BaseInputSource>) const) &genesis::population::BedReader::read_as_genome_locus_set, "Read an input source, and return its content as a GenomeLocusSet.\n\n This only uses the first three columns, `chrom`, `chromStart`, and `chromEnd`,\n and ignores everything else.\n\n This is the recommended way to read an input for testing whether genome coordinates\n are covered (filtered / to be considered) for downstream analyses.\n\nC++: genesis::population::BedReader::read_as_genome_locus_set(class std::shared_ptr<class genesis::utils::BaseInputSource>) const --> class genesis::population::GenomeLocusSet", pybind11::arg("source"));
		cl.def("read_as_genome_region_list", [](genesis::population::BedReader const &o, class std::shared_ptr<class genesis::utils::BaseInputSource> const & a0) -> genesis::population::GenomeRegionList { return o.read_as_genome_region_list(a0); }, "", pybind11::arg("source"));
		cl.def("read_as_genome_region_list", (class genesis::population::GenomeRegionList (genesis::population::BedReader::*)(class std::shared_ptr<class genesis::utils::BaseInputSource>, bool) const) &genesis::population::BedReader::read_as_genome_region_list, "Read a BED input source, and return its content as a GenomeRegionList.\n\n This only uses the first three columns, `chrom`, `chromStart`, and `chromEnd`,\n and ignores everything else.\n\n If  is set, the individual regions of the file are merged if they overlap.\n This is more useful of the region list is used to determine coverage, and less useful if\n regions are meant to indicate some specific parts of the genome, such as genes.\n See the `overlap` flag of GenomeRegionList::add( GenomeLocus const&, bool ) for details.\n\nC++: genesis::population::BedReader::read_as_genome_region_list(class std::shared_ptr<class genesis::utils::BaseInputSource>, bool) const --> class genesis::population::GenomeRegionList", pybind11::arg("source"), pybind11::arg("merge"));
		cl.def("read_as_genome_region_list", [](genesis::population::BedReader const &o, class std::shared_ptr<class genesis::utils::BaseInputSource> const & a0, class genesis::population::GenomeRegionList & a1) -> void { return o.read_as_genome_region_list(a0, a1); }, "", pybind11::arg("source"), pybind11::arg("target"));
		cl.def("read_as_genome_region_list", (void (genesis::population::BedReader::*)(class std::shared_ptr<class genesis::utils::BaseInputSource>, class genesis::population::GenomeRegionList &, bool) const) &genesis::population::BedReader::read_as_genome_region_list, "Read a BED input source, and add its content to an existing GenomeRegionList.\n\n  BedReader::read_as_genome_region_list( std::shared_ptr< genesis::utils::BaseInputSource >, bool ) const\n\nC++: genesis::population::BedReader::read_as_genome_region_list(class std::shared_ptr<class genesis::utils::BaseInputSource>, class genesis::population::GenomeRegionList &, bool) const --> void", pybind11::arg("source"), pybind11::arg("target"), pybind11::arg("merge"));

		{ // genesis::population::BedReader::Feature file:genesis/population/formats/bed_reader.hpp line:106
			auto & enclosing_class = cl;
			pybind11::class_<genesis::population::BedReader::Feature, std::shared_ptr<genesis::population::BedReader::Feature>> cl(enclosing_class, "Feature", "Store all values that can typically appear in the columns of a BED file.\n\n The order of fields in the struct is the same as the order of columns.\n If the file does not have all the columns, the remaining values here are simply left empty\n or at 0.");
			cl.def( pybind11::init( [](){ return new genesis::population::BedReader::Feature(); } ) );
			cl.def( pybind11::init( [](genesis::population::BedReader::Feature const &o){ return new genesis::population::BedReader::Feature(o); } ) );
			cl.def_readwrite("chrom", &genesis::population::BedReader::Feature::chrom);
			cl.def_readwrite("chrom_start", &genesis::population::BedReader::Feature::chrom_start);
			cl.def_readwrite("chrom_end", &genesis::population::BedReader::Feature::chrom_end);
			cl.def_readwrite("name", &genesis::population::BedReader::Feature::name);
			cl.def_readwrite("score", &genesis::population::BedReader::Feature::score);
			cl.def_readwrite("strand", &genesis::population::BedReader::Feature::strand);
			cl.def_readwrite("thick_start", &genesis::population::BedReader::Feature::thick_start);
			cl.def_readwrite("thick_end", &genesis::population::BedReader::Feature::thick_end);
			cl.def_readwrite("item_rgb", &genesis::population::BedReader::Feature::item_rgb);
			cl.def_readwrite("block_count", &genesis::population::BedReader::Feature::block_count);
			cl.def_readwrite("block_sizes", &genesis::population::BedReader::Feature::block_sizes);
			cl.def_readwrite("block_starts", &genesis::population::BedReader::Feature::block_starts);
			cl.def("assign", (struct genesis::population::BedReader::Feature & (genesis::population::BedReader::Feature::*)(const struct genesis::population::BedReader::Feature &)) &genesis::population::BedReader::Feature::operator=, "C++: genesis::population::BedReader::Feature::operator=(const struct genesis::population::BedReader::Feature &) --> struct genesis::population::BedReader::Feature &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		}

	}
}
