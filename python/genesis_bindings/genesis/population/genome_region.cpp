#include <functional>
#include <genesis/population/genome_locus.hpp>
#include <genesis/population/genome_region.hpp>
#include <genesis/population/genome_region_list.hpp>
#include <genesis/utils/containers/interval_tree.hpp>
#include <genesis/utils/containers/interval_tree/interval.hpp>
#include <genesis/utils/containers/interval_tree/iterator.hpp>
#include <genesis/utils/containers/interval_tree/node.hpp>
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

void bind_genesis_population_genome_region(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // genesis::population::GenomeRegion file:genesis/population/genome_region.hpp line:70
		pybind11::class_<genesis::population::GenomeRegion, std::shared_ptr<genesis::population::GenomeRegion>> cl(M("genesis::population"), "GenomeRegion", "A region (between two positions) on a chromosome.\n\n This can be used to represent a gene, a feature, or just generally a region of interest,\n or even the whole chromosome (see special cases below).\n We use a simple form with a `chromosome` name, and a `start` and `end` position,\n both 1-based and inclusive (closed interval).\n\n There are some special cases:\n\n   * We use an empty `chromosome` with `start` and `end` equal to 0 to denote an empty(),\n     unspecified region.\n   * Another special case is a non-empty `chromosome` with both `start` and `end` being equal to 0,\n     which denotes the whole chromosome as the region;\n     this is however not considered to be a specified() region.\n   * All other cases are invalid, that is, an empty `chromosome` with non-zero `start` or `end`,\n     or cases where `start` or `end` are zero, but not both,\n     or where `start` is greather than `end`.\n\n \n GenomeLocus\n \n\n GenomeLocusSet\n \n\n GenomeRegionList");
		cl.def( pybind11::init( [](){ return new genesis::population::GenomeRegion(); } ), "doc" );
		cl.def( pybind11::init( [](const std::string & a0){ return new genesis::population::GenomeRegion(a0); } ), "doc" , pybind11::arg("chr"));
		cl.def( pybind11::init( [](const std::string & a0, unsigned long const & a1){ return new genesis::population::GenomeRegion(a0, a1); } ), "doc" , pybind11::arg("chr"), pybind11::arg("s"));
		cl.def( pybind11::init<const std::string &, unsigned long, unsigned long>(), pybind11::arg("chr"), pybind11::arg("s"), pybind11::arg("e") );

		cl.def( pybind11::init( [](genesis::population::GenomeRegion const &o){ return new genesis::population::GenomeRegion(o); } ) );
		cl.def_readwrite("chromosome", &genesis::population::GenomeRegion::chromosome);
		cl.def_readwrite("start", &genesis::population::GenomeRegion::start);
		cl.def_readwrite("end", &genesis::population::GenomeRegion::end);
		cl.def("empty", (bool (genesis::population::GenomeRegion::*)() const) &genesis::population::GenomeRegion::empty, "C++: genesis::population::GenomeRegion::empty() const --> bool");
		cl.def("specified", (bool (genesis::population::GenomeRegion::*)() const) &genesis::population::GenomeRegion::specified, "C++: genesis::population::GenomeRegion::specified() const --> bool");
		cl.def("assign", (struct genesis::population::GenomeRegion & (genesis::population::GenomeRegion::*)(const struct genesis::population::GenomeRegion &)) &genesis::population::GenomeRegion::operator=, "C++: genesis::population::GenomeRegion::operator=(const struct genesis::population::GenomeRegion &) --> struct genesis::population::GenomeRegion &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
	}
	{ // genesis::population::GenomeLocus file:genesis/population/genome_locus.hpp line:64
		pybind11::class_<genesis::population::GenomeLocus, std::shared_ptr<genesis::population::GenomeLocus>> cl(M("genesis::population"), "GenomeLocus", "A single locus, that is, a position (or coordinate) on a chromosome.\n\n For our purposes here, we define a locus to be one position (1-based) on one chromosome exactly.\n\n When working with multiple loci, we here often expect their chromosome names to be sorted in\n lexicographical order. Hence, for example, when comparing two loci on different chromosomes,\n we also take the ordering of their chromosome names into account.\n\n There are some special cases:\n\n   * We use an empty chromosome with position 0 to denote an empty(), unspecified locus.\n   * A non-empty chromosome with position 0 means \"any position\" on the chromosome;\n     this is however not considered to be a specified() locus.\n   * An empty chromosome with a position other than 0 is an invalid state, and will throw.\n\n \n GenomeLocusSet\n \n\n GenomeRegion\n \n\n GenomeRegionList");
		cl.def( pybind11::init( [](){ return new genesis::population::GenomeLocus(); } ), "doc" );
		cl.def( pybind11::init( [](const std::string & a0){ return new genesis::population::GenomeLocus(a0); } ), "doc" , pybind11::arg("chr"));
		cl.def( pybind11::init<const std::string &, unsigned long>(), pybind11::arg("chr"), pybind11::arg("pos") );

		cl.def( pybind11::init( [](genesis::population::GenomeLocus const &o){ return new genesis::population::GenomeLocus(o); } ) );
		cl.def_readwrite("chromosome", &genesis::population::GenomeLocus::chromosome);
		cl.def_readwrite("position", &genesis::population::GenomeLocus::position);
		cl.def("assign", (struct genesis::population::GenomeLocus & (genesis::population::GenomeLocus::*)(const struct genesis::population::GenomeLocus &)) &genesis::population::GenomeLocus::operator=, "C++: genesis::population::GenomeLocus::operator=(const struct genesis::population::GenomeLocus &) --> struct genesis::population::GenomeLocus &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("empty", (bool (genesis::population::GenomeLocus::*)() const) &genesis::population::GenomeLocus::empty, "C++: genesis::population::GenomeLocus::empty() const --> bool");
		cl.def("specified", (bool (genesis::population::GenomeLocus::*)() const) &genesis::population::GenomeLocus::specified, "C++: genesis::population::GenomeLocus::specified() const --> bool");
	}
	{ // genesis::population::EmptyGenomeData file:genesis/population/genome_region_list.hpp line:56
		pybind11::class_<genesis::population::EmptyGenomeData, std::shared_ptr<genesis::population::EmptyGenomeData>> cl(M("genesis::population"), "EmptyGenomeData", "Helper struct to define a default empty data for the classes GenomeLocus, GenomeRegion,\n and GenomeRegionList.");
		cl.def( pybind11::init( [](genesis::population::EmptyGenomeData const &o){ return new genesis::population::EmptyGenomeData(o); } ) );
		cl.def( pybind11::init( [](){ return new genesis::population::EmptyGenomeData(); } ) );
		cl.def("assign", (struct genesis::population::EmptyGenomeData & (genesis::population::EmptyGenomeData::*)(const struct genesis::population::EmptyGenomeData &)) &genesis::population::EmptyGenomeData::operator=, "C++: genesis::population::EmptyGenomeData::operator=(const struct genesis::population::EmptyGenomeData &) --> struct genesis::population::EmptyGenomeData &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
	}
	{ // genesis::population::GenomeRegionList file:genesis/population/genome_region_list.hpp line:95
		pybind11::class_<genesis::population::GenomeRegionList, std::shared_ptr<genesis::population::GenomeRegionList>> cl(M("genesis::population"), "GenomeRegionList", "List of regions in a genome, for each chromosome.\n\n The data structure stores a list of genome regions, such as coming from BED or GFF files.\n The class allows to iterate through the regions of each chromosome.\n\n It furtheremore allows querying positions, that is, whether a certain position on a chromosome\n is part of one of the stored regions. However, when many regions are stored in the list,\n and many queries need to be performed (such as when reading files and needing to check every\n position on every chromosome), this can become prohibitively slow, despite using a fast\n data structure. Use GenomeLocusSet as an alternative that is way faster when all that is needed\n is information on whether a certain position/coordinate is set or not set.\n\n Positions in the interval of each region are 1-based and inclusive, that is, we used closed\n intervals. We also offer the special case to add a whole chromosome as a region, in which case\n the is_covered() function will return `true` for all positions on that chromosome (without\n checking that the position is in fact part of the chromosome - as we do not use information\n on the lengths of chromosomes in this class). We use start and end positions equal to 0 to\n mark these special whole-chromosome cases - be aware of that when adding regions to the list.\n See also GenomeLocus, GenomeLocusSet, and GenomeRegion for related classes that have the same\n special cases.\n\n Interally, we use an \n\n\n\n\n\n\n\n");
		cl.def( pybind11::init( [](){ return new genesis::population::GenomeRegionList(); } ) );
		cl.def( pybind11::init( [](genesis::population::GenomeRegionList const &o){ return new genesis::population::GenomeRegionList(o); } ) );
		cl.def("assign", (class genesis::population::GenomeRegionList & (genesis::population::GenomeRegionList::*)(const class genesis::population::GenomeRegionList &)) &genesis::population::GenomeRegionList::operator=, "C++: genesis::population::GenomeRegionList::operator=(const class genesis::population::GenomeRegionList &) --> class genesis::population::GenomeRegionList &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("add", (void (genesis::population::GenomeRegionList::*)(const std::string &)) &genesis::population::GenomeRegionList::add, "Add a whole chromosome to the list, so that all its positions are considered to be\n covered.\n\nC++: genesis::population::GenomeRegionList::add(const std::string &) --> void", pybind11::arg("chromosome"));
		cl.def("add", [](genesis::population::GenomeRegionList &o, const std::string & a0, unsigned long const & a1, unsigned long const & a2) -> void { return o.add(a0, a1, a2); }, "", pybind11::arg("chromosome"), pybind11::arg("start"), pybind11::arg("end"));
		cl.def("add", (void (genesis::population::GenomeRegionList::*)(const std::string &, unsigned long, unsigned long, bool)) &genesis::population::GenomeRegionList::add, "Add a region to the list, given its chromosome, and start and end positions.\n\n The  cannot be empty, and we expect  <  Both  and \n are 1-based, and inclusive, that is, the interval between them is closed. The special case\n of both  and  equal to 0 means that the whole chromosome is added as an interval.\n\n  GenomeRegionList::add( GenomeLocus const&, bool )\n\nC++: genesis::population::GenomeRegionList::add(const std::string &, unsigned long, unsigned long, bool) --> void", pybind11::arg("chromosome"), pybind11::arg("start"), pybind11::arg("end"), pybind11::arg("overlap"));
		cl.def("add", [](genesis::population::GenomeRegionList &o, const struct genesis::population::GenomeLocus & a0) -> void { return o.add(a0); }, "", pybind11::arg("locus"));
		cl.def("add", (void (genesis::population::GenomeRegionList::*)(const struct genesis::population::GenomeLocus &, bool)) &genesis::population::GenomeRegionList::add, "Add a single GenomeLocus, that is, an interval covering one position on a chromosome.\n\n If  is set, we first check if there is a region already in the list that overlaps\n with the one that is to be added. If so, the new region is merged with existing one,\n instead of inserting it. This is more useful of the region list is used to determine coverage,\n and less useful if regions are meant to indicate some specific parts of the genome,\n such as genes.\n\nC++: genesis::population::GenomeRegionList::add(const struct genesis::population::GenomeLocus &, bool) --> void", pybind11::arg("locus"), pybind11::arg("overlap"));
		cl.def("add", [](genesis::population::GenomeRegionList &o, const struct genesis::population::GenomeLocus & a0, const struct genesis::population::GenomeLocus & a1) -> void { return o.add(a0, a1); }, "", pybind11::arg("start"), pybind11::arg("end"));
		cl.def("add", (void (genesis::population::GenomeRegionList::*)(const struct genesis::population::GenomeLocus &, const struct genesis::population::GenomeLocus &, bool)) &genesis::population::GenomeRegionList::add, "Add an interval between two \n\n\n\n\nC++: genesis::population::GenomeRegionList::add(const struct genesis::population::GenomeLocus &, const struct genesis::population::GenomeLocus &, bool) --> void", pybind11::arg("start"), pybind11::arg("end"), pybind11::arg("overlap"));
		cl.def("add", [](genesis::population::GenomeRegionList &o, const struct genesis::population::GenomeRegion & a0) -> void { return o.add(a0); }, "", pybind11::arg("region"));
		cl.def("add", (void (genesis::population::GenomeRegionList::*)(const struct genesis::population::GenomeRegion &, bool)) &genesis::population::GenomeRegionList::add, "Add a GenomeRegion to the list.\n\n This function ensures that regions are valid (`start < end`).\n\n  GenomeRegionList::add( GenomeLocus const&, bool )\n\nC++: genesis::population::GenomeRegionList::add(const struct genesis::population::GenomeRegion &, bool) --> void", pybind11::arg("region"), pybind11::arg("overlap"));
		cl.def("add", [](genesis::population::GenomeRegionList &o, const class genesis::population::GenomeRegionList & a0) -> void { return o.add(a0); }, "", pybind11::arg("other"));
		cl.def("add", (void (genesis::population::GenomeRegionList::*)(const class genesis::population::GenomeRegionList &, bool)) &genesis::population::GenomeRegionList::add, "Add a complete GenomeRegionList to this list.\n\n This function copies all entries of the \n\n  GenomeRegionList::add( GenomeLocus const&, bool )\n\nC++: genesis::population::GenomeRegionList::add(const class genesis::population::GenomeRegionList &, bool) --> void", pybind11::arg("other"), pybind11::arg("overlap"));
		cl.def("clear", (void (genesis::population::GenomeRegionList::*)()) &genesis::population::GenomeRegionList::clear, "Remove all stored regions from all chromosomes.\n\nC++: genesis::population::GenomeRegionList::clear() --> void");
		cl.def("clear", (void (genesis::population::GenomeRegionList::*)(const std::string &)) &genesis::population::GenomeRegionList::clear, "Remove the regions of the specified \n     \n\nC++: genesis::population::GenomeRegionList::clear(const std::string &) --> void", pybind11::arg("chromosome"));
		cl.def("is_covered", (bool (genesis::population::GenomeRegionList::*)(const std::string &, unsigned long) const) &genesis::population::GenomeRegionList::is_covered, "Return whether a given position on a chromosome is part of any of the regions\n (intervals) that are stored here.\n\nC++: genesis::population::GenomeRegionList::is_covered(const std::string &, unsigned long) const --> bool", pybind11::arg("chromosome"), pybind11::arg("position"));
		cl.def("is_covered", (bool (genesis::population::GenomeRegionList::*)(const std::string &) const) &genesis::population::GenomeRegionList::is_covered, "Return whether a whole chromosome is covered.\n\n That special case is specified by an interval that covers position 0.\n\nC++: genesis::population::GenomeRegionList::is_covered(const std::string &) const --> bool", pybind11::arg("chromosome"));
		cl.def("cover_count", [](genesis::population::GenomeRegionList const &o, const std::string & a0, unsigned long const & a1) -> unsigned long { return o.cover_count(a0, a1); }, "", pybind11::arg("chromosome"), pybind11::arg("position"));
		cl.def("cover_count", (unsigned long (genesis::population::GenomeRegionList::*)(const std::string &, unsigned long, bool) const) &genesis::population::GenomeRegionList::cover_count, "Retun the number of regions (intervals) that overlap with a given position on a\n chromosome.\n\n The is_covered() function only returns whether a position is covered at all, but does not\n tell by how many regions/intervals it is covered. This function returns that value.\n\n Note that the special \"whole chromsome\" case (marked by setting an interval that covers\n position 0) is not considered here by default, as this is likely to be not intended.\n With  this behaviour can be changed, meaning that if position 0 is also\n covered (and hence the whole chromosome is marked as covered), the resulting counter\n is incremented by 1.\n\nC++: genesis::population::GenomeRegionList::cover_count(const std::string &, unsigned long, bool) const --> unsigned long", pybind11::arg("chromosome"), pybind11::arg("position"), pybind11::arg("whole_chromosome"));
		cl.def("empty", (bool (genesis::population::GenomeRegionList::*)() const) &genesis::population::GenomeRegionList::empty, "Return whether there are chromosomes with regions stored.\n\nC++: genesis::population::GenomeRegionList::empty() const --> bool");
		cl.def("chromosome_count", (unsigned long (genesis::population::GenomeRegionList::*)() const) &genesis::population::GenomeRegionList::chromosome_count, "Return the number of chromosomes for which there are regions stored.\n\nC++: genesis::population::GenomeRegionList::chromosome_count() const --> unsigned long");
		cl.def("chromosome_names", (class std::vector<std::string, class std::allocator<std::string > > (genesis::population::GenomeRegionList::*)() const) &genesis::population::GenomeRegionList::chromosome_names, "Get a list of all stored chromosome names.\n\nC++: genesis::population::GenomeRegionList::chromosome_names() const --> class std::vector<std::string, class std::allocator<std::string > >");
		cl.def("has_chromosome", (bool (genesis::population::GenomeRegionList::*)(const std::string &) const) &genesis::population::GenomeRegionList::has_chromosome, "Return whether a chromosome is stored.\n\nC++: genesis::population::GenomeRegionList::has_chromosome(const std::string &) const --> bool", pybind11::arg("chromosome"));
		cl.def("chromosome_regions", (class genesis::utils::IntervalTree<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> & (genesis::population::GenomeRegionList::*)(const std::string &)) &genesis::population::GenomeRegionList::chromosome_regions, "For a given chromosome, return the\n \n\n\n\n\n\n\n\n\nC++: genesis::population::GenomeRegionList::chromosome_regions(const std::string &) --> class genesis::utils::IntervalTree<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &", pybind11::return_value_policy::reference_internal, pybind11::arg("chromosome"));
		cl.def("region_count", (unsigned long (genesis::population::GenomeRegionList::*)(const std::string &) const) &genesis::population::GenomeRegionList::region_count, "Return the number of regions stored for the specified \n     \n\nC++: genesis::population::GenomeRegionList::region_count(const std::string &) const --> unsigned long", pybind11::arg("chromosome"));
		cl.def("total_region_count", (unsigned long (genesis::population::GenomeRegionList::*)() const) &genesis::population::GenomeRegionList::total_region_count, "Return the number of regions stored in total, across all chromosomes.\n\nC++: genesis::population::GenomeRegionList::total_region_count() const --> unsigned long");
		cl.def("chromosome_map", (class std::map<std::string, class genesis::utils::IntervalTree<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, struct std::less<std::string >, class std::allocator<struct std::pair<const std::string, class genesis::utils::IntervalTree<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> > > > & (genesis::population::GenomeRegionList::*)()) &genesis::population::GenomeRegionList::chromosome_map, "chromosome_map() const\n\nC++: genesis::population::GenomeRegionList::chromosome_map() --> class std::map<std::string, class genesis::utils::IntervalTree<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, struct std::less<std::string >, class std::allocator<struct std::pair<const std::string, class genesis::utils::IntervalTree<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> > > > &", pybind11::return_value_policy::reference_internal);
	}
}
