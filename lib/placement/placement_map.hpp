#ifndef GENESIS_PLACEMENT_PLACEMENT_MAP_H_
#define GENESIS_PLACEMENT_PLACEMENT_MAP_H_

/**
 * @brief
 *
 * @file
 * @ingroup placement
 */

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "placement/placement_tree.hpp"
#include "placement/pquery.hpp"

namespace genesis {

// =================================================================================================
//     PlacementMap
// =================================================================================================

class PlacementMap
{
public:
    // -------------------------------------------------------------------------
    //     Constructor & Destructor
    // -------------------------------------------------------------------------

    PlacementMap () : tree_(std::make_shared<PlacementTree>()) {}
    PlacementMap (std::shared_ptr<PlacementTree> ptree) : tree_(ptree) {}
    PlacementMap (const PlacementMap& other);

    PlacementMap& operator = (const PlacementMap& other);

    ~PlacementMap();

    // -------------------------------------------------------------------------
    //     Modifiers
    // -------------------------------------------------------------------------

    Pquery* add_pquery();

    bool merge(const PlacementMap& other);

    void clear();
    void clear_placements();

    // -------------------------------------------------------------------------
    //     Accessors
    // -------------------------------------------------------------------------

    inline std::shared_ptr<PlacementTree> tree_ptr()
    {
        return tree_;
    }

    inline PlacementTree& tree()
    {
        return *tree_.get();
    }

    inline const PlacementTree& tree() const
    {
        return *tree_.get();
    }

    inline std::vector<std::unique_ptr<Pquery>>& pqueries()
    {
        return pqueries_;
    }

    inline const std::vector<std::unique_ptr<Pquery>>& pqueries() const
    {
        return pqueries_;
    }

    // TODO add pquery iterator.

    // -------------------------------------------------------------------------
    //     Helper Methods
    // -------------------------------------------------------------------------

    typedef std::unordered_map<int, PlacementTree::EdgeType*> EdgeNumMapType;
    EdgeNumMapType edge_num_map() const;

    void normalize_weight_ratios();
    void restrain_to_max_weight_placements();

    // -------------------------------------------------------------------------
    //     Placement Mass
    // -------------------------------------------------------------------------

    size_t placement_count() const;
    double placement_mass() const;

    std::vector<int> closest_leaf_depth_histogram() const;
    std::vector<int> closest_leaf_distance_histogram (
        const double min, const double max, const int bins = 10
    ) const;
    std::vector<int> closest_leaf_distance_histogram_auto (
        double& min, double& max, const int bins = 10
    ) const;

    // -------------------------------------------------------------------------
    //     Distances
    // -------------------------------------------------------------------------

    // Earth Movers Distance

    double earth_movers_distance (
        const PlacementMap& other, const bool with_pendant_length = true
    ) const;
    static double earth_movers_distance (
        const PlacementMap& left, const PlacementMap& right, const bool with_pendant_length = true
    );

    // Pairwise Distance

    double pairwise_distance (
        const PlacementMap& other, const bool with_pendant_length = true
    ) const;
    static double pairwise_distance (
        const PlacementMap& left, const PlacementMap& right, const bool with_pendant_length = true
    );

    // Center of Gravity

    // std::pair<PlacementTreeEdge, double> center_of_gravity (
    void center_of_gravity (
        const bool with_pendant_length = true
    ) const;
    double center_of_gravity_distance (
        const PlacementMap& other, const bool with_pendant_length = true
    ) const;
    static double center_of_gravity_distance (
        const PlacementMap& left, const PlacementMap& right, const bool with_pendant_length = true
    );

    // -------------------------------------------------------------------------
    //     Variance
    // -------------------------------------------------------------------------

public:
    double variance() const;

protected:
    /** @brief Intermediate POD struct used for speeding up the variance calculations. */
    typedef struct {
        size_t index;
        size_t edge_index;
        size_t primary_node_index;
        size_t secondary_node_index;

        double pendant_length;
        double proximal_length;
        double branch_length;
        double like_weight_ratio;
    } VarianceData;

    void variance_thread (
        const int                        offset,
        const int                        incr,
        const std::vector<VarianceData>* pqrys,
        const Matrix<double>*            node_distances,
        double*                          partial,
        double*                          count
    ) const;

    double variance_partial (
        const VarianceData&              place_a,
        const std::vector<VarianceData>& pqrys_b,
        const Matrix<double>&            node_distances
    ) const;

    // -------------------------------------------------------------------------
    //     Dump and Debug
    // -------------------------------------------------------------------------

public:
    std::string dump() const;
    std::string dump_tree() const;
    bool validate (bool check_values = false, bool break_on_values = false) const;

    // -------------------------------------------------------------------------
    //     Members
    // -------------------------------------------------------------------------

protected:
    std::vector<std::unique_ptr<Pquery>>         pqueries_;
    std::shared_ptr<PlacementTree>               tree_;

public:
    // There is not much to mess up here for a user, so we can simply make this public.
    std::unordered_map<std::string, std::string> metadata;
};

} // namespace genesis

#endif // include guard
