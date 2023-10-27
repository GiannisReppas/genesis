#include <genesis/taxonomy/functions/ranks.hpp>
#include <genesis/taxonomy/iterator/preorder.hpp>
#include <genesis/taxonomy/taxon.hpp>
#include <genesis/taxonomy/taxon_data.hpp>
#include <genesis/taxonomy/taxonomy.hpp>
#include <genesis/utils/containers/range.hpp>
#include <iterator>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <utility>

#include <functional>
#include <pybind11/pybind11.h>
#include <string>
#include <pybind11/functional.h>
#include <../python/custom_bindings/extensions/matrix.hpp>
#include <genesis/utils/color/functions.hpp>
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
#include <../python/custom_bindings/extensions/chromosome_iterator.hpp>
#include <pybind11/stl.h>


#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

void bind_genesis_taxonomy_iterator_preorder(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // genesis::taxonomy::IteratorPreorder file:genesis/taxonomy/iterator/preorder.hpp line:103
		pybind11::class_<genesis::taxonomy::IteratorPreorder<genesis::taxonomy::Taxonomy,genesis::taxonomy::Taxon>, std::shared_ptr<genesis::taxonomy::IteratorPreorder<genesis::taxonomy::Taxonomy,genesis::taxonomy::Taxon>>> cl(M("genesis::taxonomy"), "IteratorPreorder_genesis_taxonomy_Taxonomy_genesis_taxonomy_Taxon_t", "");
		cl.def( pybind11::init( [](){ return new genesis::taxonomy::IteratorPreorder<genesis::taxonomy::Taxonomy,genesis::taxonomy::Taxon>(); } ) );
		cl.def( pybind11::init<class genesis::taxonomy::Taxonomy &>(), pybind11::arg("taxonomy") );

		cl.def( pybind11::init( [](genesis::taxonomy::IteratorPreorder<genesis::taxonomy::Taxonomy,genesis::taxonomy::Taxon> const &o){ return new genesis::taxonomy::IteratorPreorder<genesis::taxonomy::Taxonomy,genesis::taxonomy::Taxon>(o); } ) );
		cl.def("assign", (class genesis::taxonomy::IteratorPreorder<class genesis::taxonomy::Taxonomy, class genesis::taxonomy::Taxon> & (genesis::taxonomy::IteratorPreorder<genesis::taxonomy::Taxonomy,genesis::taxonomy::Taxon>::*)(const class genesis::taxonomy::IteratorPreorder<class genesis::taxonomy::Taxonomy, class genesis::taxonomy::Taxon> &)) &genesis::taxonomy::IteratorPreorder<genesis::taxonomy::Taxonomy, genesis::taxonomy::Taxon>::operator=, "C++: genesis::taxonomy::IteratorPreorder<genesis::taxonomy::Taxonomy, genesis::taxonomy::Taxon>::operator=(const class genesis::taxonomy::IteratorPreorder<class genesis::taxonomy::Taxonomy, class genesis::taxonomy::Taxon> &) --> class genesis::taxonomy::IteratorPreorder<class genesis::taxonomy::Taxonomy, class genesis::taxonomy::Taxon> &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("dereference", (class genesis::taxonomy::IteratorPreorder<class genesis::taxonomy::Taxonomy, class genesis::taxonomy::Taxon> (genesis::taxonomy::IteratorPreorder<genesis::taxonomy::Taxonomy,genesis::taxonomy::Taxon>::*)()) &genesis::taxonomy::IteratorPreorder<genesis::taxonomy::Taxonomy, genesis::taxonomy::Taxon>::operator*, "C++: genesis::taxonomy::IteratorPreorder<genesis::taxonomy::Taxonomy, genesis::taxonomy::Taxon>::operator*() --> class genesis::taxonomy::IteratorPreorder<class genesis::taxonomy::Taxonomy, class genesis::taxonomy::Taxon>");
		cl.def("pre_increment", (class genesis::taxonomy::IteratorPreorder<class genesis::taxonomy::Taxonomy, class genesis::taxonomy::Taxon> (genesis::taxonomy::IteratorPreorder<genesis::taxonomy::Taxonomy,genesis::taxonomy::Taxon>::*)()) &genesis::taxonomy::IteratorPreorder<genesis::taxonomy::Taxonomy, genesis::taxonomy::Taxon>::operator++, "C++: genesis::taxonomy::IteratorPreorder<genesis::taxonomy::Taxonomy, genesis::taxonomy::Taxon>::operator++() --> class genesis::taxonomy::IteratorPreorder<class genesis::taxonomy::Taxonomy, class genesis::taxonomy::Taxon>");
		cl.def("post_increment", (class genesis::taxonomy::IteratorPreorder<class genesis::taxonomy::Taxonomy, class genesis::taxonomy::Taxon> (genesis::taxonomy::IteratorPreorder<genesis::taxonomy::Taxonomy,genesis::taxonomy::Taxon>::*)(int)) &genesis::taxonomy::IteratorPreorder<genesis::taxonomy::Taxonomy, genesis::taxonomy::Taxon>::operator++, "C++: genesis::taxonomy::IteratorPreorder<genesis::taxonomy::Taxonomy, genesis::taxonomy::Taxon>::operator++(int) --> class genesis::taxonomy::IteratorPreorder<class genesis::taxonomy::Taxonomy, class genesis::taxonomy::Taxon>", pybind11::arg(""));
		cl.def("__eq__", (bool (genesis::taxonomy::IteratorPreorder<genesis::taxonomy::Taxonomy,genesis::taxonomy::Taxon>::*)(const class genesis::taxonomy::IteratorPreorder<class genesis::taxonomy::Taxonomy, class genesis::taxonomy::Taxon> &) const) &genesis::taxonomy::IteratorPreorder<genesis::taxonomy::Taxonomy, genesis::taxonomy::Taxon>::operator==, "C++: genesis::taxonomy::IteratorPreorder<genesis::taxonomy::Taxonomy, genesis::taxonomy::Taxon>::operator==(const class genesis::taxonomy::IteratorPreorder<class genesis::taxonomy::Taxonomy, class genesis::taxonomy::Taxon> &) const --> bool", pybind11::arg("other"));
		cl.def("__ne__", (bool (genesis::taxonomy::IteratorPreorder<genesis::taxonomy::Taxonomy,genesis::taxonomy::Taxon>::*)(const class genesis::taxonomy::IteratorPreorder<class genesis::taxonomy::Taxonomy, class genesis::taxonomy::Taxon> &) const) &genesis::taxonomy::IteratorPreorder<genesis::taxonomy::Taxonomy, genesis::taxonomy::Taxon>::operator!=, "C++: genesis::taxonomy::IteratorPreorder<genesis::taxonomy::Taxonomy, genesis::taxonomy::Taxon>::operator!=(const class genesis::taxonomy::IteratorPreorder<class genesis::taxonomy::Taxonomy, class genesis::taxonomy::Taxon> &) const --> bool", pybind11::arg("other"));
		cl.def("taxon", (class genesis::taxonomy::Taxon & (genesis::taxonomy::IteratorPreorder<genesis::taxonomy::Taxonomy,genesis::taxonomy::Taxon>::*)() const) &genesis::taxonomy::IteratorPreorder<genesis::taxonomy::Taxonomy, genesis::taxonomy::Taxon>::taxon, "C++: genesis::taxonomy::IteratorPreorder<genesis::taxonomy::Taxonomy, genesis::taxonomy::Taxon>::taxon() const --> class genesis::taxonomy::Taxon &", pybind11::return_value_policy::reference_internal);
	}
	// genesis::taxonomy::preorder(const class genesis::taxonomy::Taxonomy &) file:genesis/taxonomy/iterator/preorder.hpp line:206
	M("genesis::taxonomy").def("preorder", (class genesis::utils::Range<class genesis::taxonomy::IteratorPreorder<const class genesis::taxonomy::Taxonomy, const class genesis::taxonomy::Taxon> > (*)(const class genesis::taxonomy::Taxonomy &)) &genesis::taxonomy::preorder<genesis::taxonomy::Taxonomy>, "C++: genesis::taxonomy::preorder(const class genesis::taxonomy::Taxonomy &) --> class genesis::utils::Range<class genesis::taxonomy::IteratorPreorder<const class genesis::taxonomy::Taxonomy, const class genesis::taxonomy::Taxon> >", pybind11::arg("taxonomy"));

	// genesis::taxonomy::preorder(class genesis::taxonomy::Taxonomy &) file:genesis/taxonomy/iterator/preorder.hpp line:216
	M("genesis::taxonomy").def("preorder", (class genesis::utils::Range<class genesis::taxonomy::IteratorPreorder<class genesis::taxonomy::Taxonomy, class genesis::taxonomy::Taxon> > (*)(class genesis::taxonomy::Taxonomy &)) &genesis::taxonomy::preorder<genesis::taxonomy::Taxonomy>, "C++: genesis::taxonomy::preorder(class genesis::taxonomy::Taxonomy &) --> class genesis::utils::Range<class genesis::taxonomy::IteratorPreorder<class genesis::taxonomy::Taxonomy, class genesis::taxonomy::Taxon> >", pybind11::arg("taxonomy"));

	// genesis::taxonomy::rank_from_abbreviation(char) file:genesis/taxonomy/functions/ranks.hpp line:44
	M("genesis::taxonomy").def("rank_from_abbreviation", (std::string (*)(char)) &genesis::taxonomy::rank_from_abbreviation, "C++: genesis::taxonomy::rank_from_abbreviation(char) --> std::string", pybind11::arg("r"));

	// genesis::taxonomy::rank_to_abbreviation(const std::string &) file:genesis/taxonomy/functions/ranks.hpp line:45
	M("genesis::taxonomy").def("rank_to_abbreviation", (std::string (*)(const std::string &)) &genesis::taxonomy::rank_to_abbreviation, "C++: genesis::taxonomy::rank_to_abbreviation(const std::string &) --> std::string", pybind11::arg("rank"));

	// genesis::taxonomy::resolve_rank_abbreviation(const std::string &) file:genesis/taxonomy/functions/ranks.hpp line:47
	M("genesis::taxonomy").def("resolve_rank_abbreviation", (struct std::pair<std::string, std::string > (*)(const std::string &)) &genesis::taxonomy::resolve_rank_abbreviation, "C++: genesis::taxonomy::resolve_rank_abbreviation(const std::string &) --> struct std::pair<std::string, std::string >", pybind11::arg("entry"));

}
