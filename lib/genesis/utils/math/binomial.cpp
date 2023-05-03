/*
    Genesis - A toolkit for working with phylogenetic data.
    Copyright (C) 2014-2023 Lucas Czech

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Contact:
    Lucas Czech <lczech@carnegiescience.edu>
    Department of Plant Biology, Carnegie Institution For Science
    260 Panama Street, Stanford, CA 94305, USA
*/

/**
 * @brief
 *
 * @file
 * @ingroup utils
 */

#include "genesis/utils/math/binomial.hpp"

#include "genesis/utils/math/common.hpp"

#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace genesis {
namespace utils {

// =================================================================================================
//     Helper Functions
// =================================================================================================

// /**
//  * @brief Largest value for `n` when computing binomial coefficients where no value of `k` causes
//  * the result to overflow.
//  *
//  * See binomial_coefficient_approx() for details.
//  */
// constexpr size_t MAX_BINOMIAL_COEFFICIENT_N = 1029;
//
// // Make sure that the list and the magic number are the same.
// static_assert(
//     log_factorial_lookup_.size() == MAX_BINOMIAL_COEFFICIENT_N,
//     "log_factorial_lookup_.size() != MAX_BINOMIAL_COEFFICIENT_N"
// );
//
// // We also have that magic number in some doxygen comments,
// // so we'd need to update that as well if this number changes at some point.
// static_assert(
//     MAX_BINOMIAL_COEFFICIENT_N == 1029,
//     "Need to update documentation: MAX_BINOMIAL_COEFFICIENT_N != 1029"
// );

/**
 * @brief Log-factorial log(x!) lookup table for fast computation of binomial coefficients.
 * See binomial_coefficient_approx() for usage, and see log_factorial_lookup_generator_()
 * for the generator function.
 */
static const std::array<double, 1024> log_factorial_lookup_ = {{
    0.0000000000000000, 0.0000000000000000, 0.6931471805599452, 1.7917594692280550, 3.1780538303479453,
    4.7874917427820458, 6.5792512120101012, 8.5251613610654147, 10.604602902745251, 12.801827480081471,
    15.104412573075518, 17.502307845873887, 19.987214495661888, 22.552163853123425, 25.191221182738683,
    27.899271383840894, 30.671860106080675, 33.505073450136891, 36.395445208033053, 39.339884187199495,
    42.335616460753485, 45.380138898476908, 48.471181351835227, 51.606675567764377, 54.784729398112326,
    58.003605222980525, 61.261701761002008, 64.557538627006338, 67.889743137181540, 71.257038967168015,
    74.658236348830172, 78.092223553315321, 81.557959456115043, 85.054467017581530, 88.580827542197696,
    92.136175603687107, 95.719694542143216, 99.330612454787442, 102.96819861451382, 106.63176026064347,
    110.32063971475741, 114.03421178146171, 117.77188139974507, 121.53308151543864, 125.31727114935690,
    129.12393363912722, 132.95257503561632, 136.80272263732638, 140.67392364823428, 144.56574394634490,
    148.47776695177305, 152.40959258449737, 156.36083630307880, 160.33112821663093, 164.32011226319520,
    168.32744544842768, 172.35279713916282, 176.39584840699737, 180.45629141754378, 184.53382886144951,
    188.62817342367160, 192.73904728784490, 196.86618167288998, 201.00931639928152, 205.16819948264120,
    209.34258675253685, 213.53224149456327, 217.73693411395422, 221.95644181913033, 226.19054832372760,
    230.43904356577696, 234.70172344281826, 238.97838956183432, 243.26884900298271, 247.57291409618688,
    251.89040220972319, 256.22113555000954, 260.56494097186322, 264.92164979855283, 269.29109765101987,
    273.67312428569375, 278.06757344036617, 282.47429268763045, 286.89313329542705, 291.32395009427034,
    295.76660135076065, 300.22094864701415, 304.68685676566872, 309.16419358014696, 313.65282994987911,
    318.15263962020936, 322.66349912672621, 327.18528770377526, 331.71788719692853, 336.26118197919851,
    340.81505887079908, 345.37940706226692, 349.95411804077031, 354.53908551944090, 359.13420536957551,
    363.73937555556358, 368.35449607240486, 372.97946888568913, 377.61419787391878, 382.25858877306018,
    386.91254912321773, 391.57598821732978, 396.24881705179166, 400.93094827891588, 405.62229616114502,
    410.32277652693745, 415.03230672824981, 419.75080559954489, 424.47819341825721, 429.21439186665168,
    433.95932399501493, 438.71291418612128, 443.47508812091905, 448.24577274538473, 453.02489623849624,
    457.81238798127828, 462.60817852687501, 467.41219957160826, 472.22438392698069, 477.04466549258575,
    481.87297922988807, 486.70926113683953, 491.55344822329812, 496.40547848721775, 501.26529089157941,
    506.13282534203501, 511.00802266523618, 515.89082458782252, 520.78117371604424, 525.67901351599517,
    530.58428829443358, 535.49694318016964, 540.41692410599774, 545.34417779115495, 550.27865172428562,
    555.22029414689496, 560.16905403727310, 565.12488109487435, 570.08772572513431, 575.05753902471031,
    580.03427276713091, 585.01787938883922, 590.00831197561797, 595.00552424938212, 600.00947055532754,
    605.02010584942377, 610.03738568623874, 615.06126620708505, 620.09170412847755, 625.12865673089118,
    630.17208184781043, 635.22193785505999, 640.27818366040833, 645.34077869343525, 650.40968289565546,
    655.48485671088929, 660.56626107587374, 665.65385741110617, 670.74760761191294, 675.84747403973711,
    680.95341951363764, 686.06540730199413, 691.18340111441091, 696.30736509381416, 701.43726380873727,
    706.57306224578758, 711.71472580229022, 716.86222027910367, 722.01551187360144, 727.17456717281596,
    732.33935314673943, 737.50983714177755, 742.68598687435133, 747.86777042464337, 753.05515623048416,
    758.24811308137441, 763.44661011264020, 768.65061679971700, 773.86010295255846, 779.07503871016741,
    784.29539453524569, 789.52114120895885, 794.75224982581346, 799.98869178864345, 805.23043880370312,
    810.47746287586358, 815.72973630391016, 820.98723167593789, 826.24992186484280, 831.51778002390608,
    836.79077958246978, 842.06889424170026, 847.35209797043831, 852.64036500113286, 857.93366982585735,
    863.23198719240543, 868.53529210046452, 873.84355979786574, 879.15676577690749, 884.47488577075171,
    889.79789574989013, 895.12577191867967, 900.45849071194505, 905.79602879164634, 911.13836304361109,
    916.48547057432859, 921.83732870780466, 927.19391498247671, 932.55520714818613, 937.92118316320796,
    943.29182119133566, 948.66709959901982, 954.04699695256033, 959.43149201534948, 964.82056374516594,
    970.21419129151832, 975.61235399303609, 981.01503137490840, 986.42220314636847, 991.83384919822356,
    997.24994960042795, 1002.6704845997002, 1008.0954346171816, 1013.5247802461361, 1018.9585022496904,
    1024.3965815586137, 1029.8389992691355, 1035.2857366408018, 1040.7367750943674, 1046.1920962097252,
    1051.6516817238694, 1057.1155135288950, 1062.5835736700301, 1068.0558443437017, 1073.5323078956333,
    1079.0129468189753, 1084.4977437524658, 1089.9866814786226, 1095.4797429219632, 1100.9769111472565,
    1106.4781693578011, 1111.9835008937334, 1117.4928892303615, 1123.0063179765264, 1128.5237708729910,
    1134.0452317908532, 1139.5706847299850, 1145.1001138174965, 1150.6335033062242, 1156.1708375732428,
    1161.7121011184013, 1167.2572785628809, 1172.8063546477761, 1178.3593142326977, 1183.9161422943971,
    1189.4768239254126, 1195.0413443327354, 1200.6096888364966, 1206.1818428686745, 1211.7577919718208,
    1217.3375217978071, 1222.9210181065887, 1228.5082667649890, 1234.0992537454999, 1239.6939651251018,
    1245.2923870841003, 1250.8945059049800, 1256.5003079712760, 1262.1097797664611, 1267.7229078728492,
    1273.3396789705157, 1278.9600798362328, 1284.5840973424201, 1290.2117184561107, 1295.8429302379320,
    1301.4777198411014, 1307.1160745104351, 1312.7579815813731, 1318.4034284790164, 1324.0524027171775,
    1329.7048918974463, 1335.3608837082661, 1341.0203659240258, 1346.6833264041618, 1352.3497530922741,
    1358.0196340152547, 1363.6929572824263, 1369.3697110846945, 1375.0498836937115, 1380.7334634610502,
    1386.4204388173900, 1392.1107982717142, 1397.8045304105169, 1403.5016238970222, 1409.2020674704129,
    1414.9058499450691, 1420.6129602098181, 1426.3233872271931, 1432.0371200327024, 1437.7541477341088,
    1443.4744595107161, 1449.1980446126686, 1454.9248923602559, 1460.6549921432295, 1466.3883334201273,
    1472.1249057176065, 1477.8646986297856, 1483.6077018175952, 1489.3539050081354, 1495.1032979940437,
    1500.8558706328693, 1506.6116128464562, 1512.3705146203336, 1518.1325660031137, 1523.8977571058986,
    1529.6660781016924, 1535.4375192248224, 1541.2120707703668, 1546.9897230935894, 1552.7704666093819,
    1558.5542917917116, 1564.3411891730784, 1570.1311493439757, 1575.9241629523599, 1581.7202207031253,
    1587.5193133575858, 1593.3214317329630, 1599.1265667018795, 1604.9347091918598, 1610.7458501848366,
    1616.5599807166616, 1622.3770918766247, 1628.1971748069770, 1634.0202207024602, 1639.8462208098406,
    1645.6751664274509, 1651.5070489047343, 1657.3418596417969, 1663.1795900889629, 1669.0202317463363,
    1674.8637761633677, 1680.7102149384255, 1686.5595397183722, 1692.4117421981466, 1698.2668141203490,
    1704.1247472748323, 1709.9855334982981, 1715.8491646738962, 1721.7156327308296, 1727.5849296439633,
    1733.4570474334387, 1739.3319781642906, 1745.2097139460702, 1751.0902469324710, 1756.9735693209593,
    1762.8596733524096, 1768.7485513107424, 1774.6401955225681, 1780.5345983568329, 1786.4317522244696,
    1792.3316495780521, 1798.2342829114534, 1804.1396447595080, 1810.0477276976769, 1815.9585243417175,
    1821.8720273473557, 1827.7882294099632, 1833.7071232642363, 1839.6287016838801, 1845.5529574812947,
    1851.4798835072652, 1857.4094726506551, 1863.3417178381030, 1869.2766120337226, 1875.2141482388049,
    1881.1543194915253, 1887.0971188666520, 1893.0425394752585, 1898.9905744644391, 1904.9412170170267,
    1910.8944603513146, 1916.8502977207795, 1922.8087224138094, 1928.7697277534326, 1934.7333070970510,
    1940.6994538361746, 1946.6681613961600, 1952.6394232359505, 1958.6132328478197, 1964.5895837571177,
    1970.5684695220189, 1976.5498837332734, 1982.5338200139606, 1988.5202720192451, 1994.5092334361350,
    2000.5006979832431, 2006.4946594105497, 2012.4911114991687, 2018.4900480611154, 2024.4914629390767,
    2030.4953500061831, 2036.5017031657849, 2042.5105163512276, 2048.5217835256317, 2054.5354986816747,
    2060.5516558413728, 2066.5702490558692, 2072.5912724052187, 2078.6147199981797, 2084.6405859720048,
    2090.6688644922356, 2096.6995497524968, 2102.7326359742956, 2108.7681174068202, 2114.8059883267424,
    2120.8462430380200, 2126.8888758717026, 2132.9338811857388, 2138.9812533647851, 2145.0309868200170,
    2151.0830759889413, 2157.1375153352105, 2163.1942993484390, 2169.2534225440209, 2175.3148794629487,
    2181.3786646716362, 2187.4447727617398, 2193.5131983499841, 2199.5839360779864, 2205.6569806120870,
    2211.7323266431758, 2217.8099688865250, 2223.8899020816207, 2229.9721209919971, 2236.0566204050724,
    2242.1433951319846, 2248.2324400074313, 2254.3237498895091, 2260.4173196595543, 2266.5131442219867,
    2272.6112185041529, 2278.7115374561731, 2284.8140960507867, 2290.9188892832017, 2297.0259121709441,
    2303.1351597537086, 2309.2466270932114, 2315.3603092730436, 2321.4762013985269, 2327.5942985965680,
    2333.7145960155190, 2339.8370888250333, 2345.9617722159273, 2352.0886414000415, 2358.2176916101021,
    2364.3489180995853, 2370.4823161425820, 2376.6178810336637, 2382.7556080877498, 2388.8954926399761,
    2395.0375300455635, 2401.1817156796892, 2407.3280449373583, 2413.4765132332759, 2419.6271160017222,
    2425.7798486964261, 2431.9347067904428, 2438.0916857760285, 2444.2507811645205, 2450.4119884862157,
    2456.5753032902503, 2462.7407211444815, 2468.9082376353699, 2475.0778483678614, 2481.2495489652724,
    2487.4233350691743, 2493.5992023392801, 2499.7771464533307, 2505.9571631069834, 2512.1392480137001,
    2518.3233969046378, 2524.5096055285385, 2530.6978696516212, 2536.8881850574744, 2543.0805475469492,
    2549.2749529380540, 2555.4713970658486, 2561.6698757823410, 2567.8703849563835, 2574.0729204735712,
    2580.2774782361398, 2586.4840541628646, 2592.6926441889614, 2598.9032442659859, 2605.1158503617376,
    2611.3304584601597, 2617.5470645612445, 2623.7656646809364, 2629.9862548510359, 2636.2088311191073,
    2642.4333895483828, 2648.6599262176701, 2654.8884372212615, 2661.1189186688398, 2667.3513666853905,
    2673.5857774111091, 2679.8221470013127, 2686.0604716263524, 2692.3007474715232, 2698.5429707369785,
    2704.7871376376424, 2711.0332444031242, 2717.2812872776326, 2723.5312625198922, 2729.7831664030582,
    2736.0369952146339, 2742.2927452563872, 2748.5504128442699, 2754.8099943083348, 2761.0714859926557,
    2767.3348842552473, 2773.6001854679848, 2779.8673860165263, 2786.1364823002327, 2792.4074707320910,
    2798.6803477386370, 2804.9551097598787, 2811.2317532492202, 2817.5102746733860, 2823.7906705123460,
    2830.0729372592418, 2836.3570714203124, 2842.6430695148215, 2848.9309280749831, 2855.2206436458919,
    2861.5122127854502, 2867.8056320642968, 2874.1008980657366, 2880.3980073856706, 2886.6969566325265,
    2892.9977424271897, 2899.3003614029344, 2905.6048102053564, 2911.9110854923047, 2918.2191839338143,
    2924.5291022120409, 2930.8408370211937, 2937.1543850674707, 2943.4697430689930, 2949.7869077557402,
    2956.1058758694867, 2962.4266441637374, 2968.7492094036647, 2975.0735683660459, 2981.3997178392010,
    2987.7276546229300, 2994.0573755284527, 3000.3888773783465, 3006.7221570064862, 3013.0572112579844,
    3019.3940369891307, 3025.7326310673338, 3032.0729903710617, 3038.4151117897827, 3044.7589922239090,
    3051.1046285847374, 3057.4520177943932, 3063.8011567857729, 3070.1520425024878, 3076.5046718988074,
    3082.8590419396046, 3089.2151496003003, 3095.5729918668085, 3101.9325657354807, 3108.2938682130539,
    3114.6568963165942, 3121.0216470734463, 3127.3881175211777, 3133.7563047075282, 3140.1262056903565,
    3146.4978175375882, 3152.8711373271653, 3159.2461621469934, 3165.6228890948919, 3172.0013152785436,
    3178.3814378154434, 3184.7632538328494, 3191.1467604677332, 3197.5319548667308, 3203.9188341860936,
    3210.3073955916393, 3216.6976362587047, 3223.0895533720973, 3229.4831441260480, 3235.8784057241637,
    3242.2753353793801, 3248.6739303139152, 3255.0741877592241, 3261.4761049559511, 3267.8796791538857,
    3274.2849076119164, 3280.6917875979857, 3287.1003163890450, 3293.5104912710112, 3299.9223095387210,
    3306.3357684958883, 3312.7508654550597, 3319.1675977375721, 3325.5859626735082, 3332.0059576016552,
    3338.4275798694616, 3344.8508268329952, 3351.2756958569007, 3357.7021843143584, 3364.1302895870431,
    3370.5600090650823, 3376.9913401470158, 3383.4242802397548, 3389.8588267585424, 3396.2949771269118,
    3402.7327287766484, 3409.1720791477487, 3415.6130256883816, 3422.0555658548496, 3428.4996971115502,
    3434.9454169309356, 3441.3927227934769, 3447.8416121876239, 3454.2920826097679, 3460.7441315642050,
    3467.1977565630978, 3473.6529551264380, 3480.1097247820103, 3486.5680630653551, 3493.0279675197326,
    3499.4894356960863, 3505.9524651530069, 3512.4170534566970, 3518.8831981809344, 3525.3508969070390,
    3531.8201472238347, 3538.2909467276172, 3544.7632930221180, 3551.2371837184701, 3557.7126164351744,
    3564.1895887980641, 3570.6680984402728, 3577.1481430021995, 3583.6297201314760, 3590.1128274829334,
    3596.5974627185687, 3603.0836235075130, 3609.5713075259978, 3616.0605124573231, 3622.5512359918257,
    3629.0434758268461, 3635.5372296666978, 3642.0324952226347, 3648.5292702128204, 3655.0275523622968,
    3661.5273394029527, 3668.0286290734930, 3674.5314191194088, 3681.0357072929455, 3687.5414913530735,
    3694.0487690654586, 3700.5575382024304, 3707.0677965429536, 3713.5795418725984, 3720.0927719835108,
    3726.6074846743832, 3733.1236777504259, 3739.6413490233381, 3746.1604963112786, 3752.6811174388372,
    3759.2032102370072, 3765.7267725431566, 3772.2518022009999, 3778.7782970605708, 3785.3062549781935,
    3791.8356738164557, 3798.3665514441814, 3804.8988857364038, 3811.4326745743374, 3817.9679158453509,
    3824.5046074429424, 3831.0427472667102, 3837.5823332223281, 3844.1233632215180, 3850.6658351820247,
    3857.2097470275894, 3863.7550966879239, 3870.3018820986845, 3876.8501012014467, 3883.3997519436807,
    3889.9508322787242, 3896.5033401657588, 3903.0572735697847, 3909.6126304615955, 3916.1694088177537,
    3922.7276066205659, 3929.2872218580592, 3935.8482525239556, 3942.4106966176491, 3948.9745521441814,
    3955.5398171142169, 3962.1064895440200, 3968.6745674554318, 3975.2440488758461, 3981.8149318381857,
    3988.3872143808799, 3994.9608945478403, 4001.5359703884401, 4008.1124399574883, 4014.6903013152091,
    4021.2695525272193, 4027.8501916645041, 4034.4322168033968, 4041.0156260255558, 4047.6004174179416,
    4054.1865890727963, 4060.7741390876213, 4067.3630655651550, 4073.9533666133516, 4080.5450403453601,
    4087.1380848795025, 4093.7324983392523, 4100.3282788532133, 4106.9254245551001, 4113.5239335837150,
    4120.1238040829276, 4126.7250342016569, 4133.3276220938460, 4139.9315659184467, 4146.5368638393948,
    4153.1435140255926, 4159.7515146508886, 4166.3608638940559, 4172.9715599387737, 4179.5836009736067,
    4186.1969851919866, 4192.8117107921908, 4199.4277759773240, 4206.0451789552981, 4212.6639179388148,
    4219.2839911453448, 4225.9053967971086, 4232.5281331210581, 4239.1521983488583, 4245.7775907168661,
    4252.4043084661153, 4259.0323498422949, 4265.6617130957320, 4272.2923964813745, 4278.9243982587705,
    4285.5577166920511, 4292.1923500499124, 4298.8282966055995, 4305.4655546368840, 4312.1041224260507,
    4318.7439982598771, 4325.3851804296173, 4332.0276672309847, 4338.6714569641326, 4345.3165479336385,
    4351.9629384484861, 4358.6106268220492, 4365.2596113720738, 4371.9098904206612, 4378.5614622942512,
    4385.2143253236045, 4391.8684778437873, 4398.5239181941552, 4405.1806447183335, 4411.8386557642043,
    4418.4979496838878, 4425.1585248337278, 4431.8203795742729, 4438.4835122702634, 4445.1479212906142,
    4451.8136050083967, 4458.4805618008259, 4465.1487900492430, 4471.8182881391012, 4478.4890544599475,
    4485.1610874054086, 4491.8343853731758, 4498.5089467649905, 4505.1847699866257, 4511.8618534478728,
    4518.5401955625275, 4525.2197947483719, 4531.9006494271625, 4538.5827580246123, 4545.2661189703786,
    4551.9507306980468, 4558.6365916451150, 4565.3237002529813, 4572.0120549669282, 4578.7016542361071,
    4585.3924965135257, 4592.0845802560325, 4598.7779039243023, 4605.4724659828235, 4612.1682648998822,
    4618.8652991475483, 4625.5635672016633, 4632.2630675418250, 4638.9637986513726, 4645.6657590173754,
    4652.3689471306161, 4659.0733614855799, 4665.7790005804400, 4672.4858629170431, 4679.1939470008965,
    4685.9032513411548, 4692.6137744506077, 4699.3255148456637, 4706.0384710463404, 4712.7526415762495,
    4719.4680249625844, 4726.1846197361056, 4732.9024244311295, 4739.6214375855143, 4746.3416577406497,
    4753.0630834414405, 4759.7857132362960, 4766.5095456771169, 4773.2345793192835, 4779.9608127216425,
    4786.6882444464936, 4793.4168730595784, 4800.1466971300679, 4806.8777152305502, 4813.6099259370176,
    4820.3433278288549, 4827.0779194888282, 4833.8136995030709, 4840.5506664610730, 4847.2888189556688,
    4854.0281555830261, 4860.7686749426321, 4867.5103756372837, 4874.2532562730757, 4880.9973154593872,
    4887.7425518088712, 4894.4889639374442, 4901.2365504642739, 4907.9853100117653, 4914.7352412055534,
    4921.4863426744905, 4928.2386130506320, 4934.9920509692301, 4941.7466550687177, 4948.5024239907016,
    4955.2593563799492, 4962.0174508843766, 4968.7767061550403, 4975.5371208461238, 4982.2986936149282,
    4989.0614231218597, 4995.8253080304221, 5002.5903470072026, 5009.3565387218632, 5016.1238818471284,
    5022.8923750587774, 5029.6620170356300, 5036.4328064595393, 5043.2047420153785, 5049.9778223910344,
    5056.7520462773919, 5063.5274123683284, 5070.3039193607010, 5077.0815659543359, 5083.8603508520209,
    5090.6402727594932, 5097.4213303854294, 5104.2035224414358, 5110.9868476420397, 5117.7713047046773,
    5124.5568923496849, 5131.3436093002902, 5138.1314542825994, 5144.9204260255920, 5151.7105232611057,
    5158.5017447238315, 5165.2940891513026, 5172.0875552838825, 5178.8821418647585, 5185.6778476399322,
    5192.4746713582072, 5199.2726117711818, 5206.0716676332404, 5212.8718377015430, 5219.6731207360144,
    5226.4755154993391, 5233.2790207569478, 5240.0836352770102, 5246.8893578304269, 5253.6961871908188,
    5260.5041221345191, 5267.3131614405620, 5274.1233038906776, 5280.9345482692788, 5287.7468933634564,
    5294.5603379629674, 5301.3748808602277, 5308.1905208503022, 5315.0072567308971, 5321.8250873023517,
    5328.6440113676272, 5335.4640277323015, 5342.2851352045582, 5349.1073325951784, 5355.9306187175343,
    5362.7549923875777, 5369.5804524238329, 5376.4069976473893, 5383.2346268818919, 5390.0633389535333,
    5396.8931326910460, 5403.7240069256923, 5410.5559604912578, 5417.3889922240442, 5424.2231009628576,
    5431.0582855490047, 5437.8945448262821, 5444.7318776409675, 5451.5702828418152, 5458.4097592800445,
    5465.2503058093334, 5472.0919212858107, 5478.9346045680495, 5485.7783545170560, 5492.6231699962646,
    5499.4690498715290, 5506.3159930111142, 5513.1639982856905, 5520.0130645683239, 5526.8631907344698,
    5533.7143756619635, 5540.5666182310151, 5547.4199173242014, 5554.2742718264562, 5561.1296806250666,
    5567.9861426096613, 5574.8436566722066, 5581.7022217069980, 5588.5618366106519, 5595.4225002821004,
    5602.2842116225811, 5609.1469695356327, 5616.0107729270858, 5622.8756207050565, 5629.7415117799401,
    5636.6084450644021, 5643.4764194733725, 5650.3454339240379, 5657.2154873358359, 5664.0865786304466,
    5670.9587067317852, 5677.8318705659976, 5684.7060690614508, 5691.5813011487271, 5698.4575657606183,
    5705.3348618321161, 5712.2131883004076, 5719.0925441048685, 5725.9729281870541, 5732.8543394906965,
    5739.7367769616940, 5746.6202395481068, 5753.5047262001499, 5760.3902358701844, 5767.2767675127152,
    5774.1643200843801, 5781.0528925439457, 5787.9424838523000, 5794.8330929724470, 5801.7247188694992,
    5808.6173605106715, 5815.5110168652745, 5822.4056869047081, 5829.3013696024564, 5836.1980639340791,
    5843.0957688772078, 5849.9944834115377, 5856.8942065188221, 5863.7949371828672, 5870.6966743895237,
    5877.5994171266821, 5884.5031643842667, 5891.4079151542282, 5898.3136684305400, 5905.2204232091890,
    5912.1281784881712, 5919.0369332674863, 5925.9466865491313, 5932.8574373370930, 5939.7691846373446,
    5946.6819274578374, 5953.5956648084975, 5960.5103957012161, 5967.4261191498472, 5974.3428341702011,
    5981.2605397800362, 5988.1792349990565, 5995.0989188489038, 6002.0195903531521, 6008.9412485373032,
    6015.8638924287789, 6022.7875210569173, 6029.7121334529656, 6036.6377286500765, 6043.5643056832996,
    6050.4918635895783, 6057.4204014077432, 6064.3499181785064, 6071.2804129444585
}};

// constexpr version to generate the above table. Does only work in C++ >14, but we use C++11 here.
// We could probably rewrite this to use some template loop unrolling at compile time via
// variadic template argument lists. But just not worth the effort for now. Also, we might run into
// issues with the maximum template instantiation depth...

// template<size_t n>
// struct LogFactorial{
//     std::array<double, n> data;
//
//     constexpr LogFactorial()
//         : data( 0.0 )
//     {
//         // That loop needs C++14 or above...
//         for( size_t i = 1; i < n; ++i ) {
//             data[i] = data[i-1] + constexpr_log(i);
//         }
//     }
//
//     constexpr double constexpr_log( double x ) const
//     {
//         // We need to wrap this, as std::log is not marked constexpr, but is.
//         return std::log(x);
//     }
//
//     double operator[]( size_t i ) const
//     {
//         // Only called locally from within this source file, so we assume that the range is valid.
//         // Adapt to proper boundary check if this is also exposed to the outside at some point.
//         assert( i < n );
//         return data[i];
//     }
//
//     size_t size() const
//     {
//         return n;
//     }
// };
//
// Create a lookup table that behaves the same as the static std::array, but is filled at compile time.
// constexpr auto const log_factorial_lookup_ = LogFactorial<1024>();

/**
 * @brief Helper function to generate above lookup table.
 *
 * The function is not called from anywhere, but kept here for reference, in case we want to
 * modify the above lookup table. Computes log(x!), which we do neatly in an iterative way:
 * x! = (x-1)! * x ==> log(x!) = log((x-1)!) + log(x)
 * See https://stackoverflow.com/a/37715980/4184258
 */
std::vector<double> log_factorial_lookup_generator_()
{
    // It's stupidly hard to get double to string with a fixed number of digits (so that our
    // printed out table is neatly aligned), while also ensuring correct rounding...
    auto double_to_string = []( double val ){
        std::ostringstream s;
        s.precision( 17 );
        s << val;
        if( val == 0.0 ) {
            return std::string( "0.0000000000000000" );
        } else if( s.str().size() > 18 ) {
            return s.str().substr( 0, 18 );
        } else if( s.str().size() < 18 ) {
            return s.str() + std::string( 18 - s.str().size(), '0' );
        } else {
            return s.str();
        }
    };

    // Prepare result.
    size_t m = 1024;
    auto logf = std::vector<double>(m);
    logf[0] = 0.0;

    // Loop and add up log(x!) = log((x-1)!) + log(x)
    std::cout << "    " << double_to_string( logf[0] ) << ", ";
    for( size_t i = 1; i < m; ++i) {
        logf[i] = logf[i-1] + std::log(i);

        std::cout << double_to_string( logf[i] ) << ", ";
        if( (i+1) % 5 == 0 ) {
            std::cout << "\n    ";
        }
    }
    std::cout << "\n";
    return logf;
}

/**
 * @brief Local helper function to check that n and k are valid for a binomial coefficient.
 */
void binomial_coefficient_check_n_k_( size_t n, size_t k )
{
    // Error cases.
    if( n == 0 ) {
        throw std::invalid_argument( "Cannot compute binomial coefficient with n == 0" );
    }
    if( k == 0 ) {
        throw std::invalid_argument( "Cannot compute binomial coefficient with k == 0" );
    }
    if( k > n ) {
        throw std::invalid_argument( "Cannot compute binomial coefficient with k > n" );
    }
}

// =================================================================================================
//     Binomial Functions
// =================================================================================================

double log_factorial( size_t n )
{
    // For small numbers, use or precise lookup table.
    if( n < log_factorial_lookup_.size() ) {
        return log_factorial_lookup_[ n ];
    }

    // Stirling's approximation for larger values. Highly accurate, although it doesn't look like it.
    // See https://www.johndcook.com/blog/2010/08/16/how-to-compute-log-factorial/
    double const x = static_cast<double>( n + 1 );
    return (x - 0.5) * std::log(x) - x + 0.5 * std::log(2 * PI) + 1.0 / (12.0 * x);
}

size_t binomial_coefficient_int( size_t n, size_t k )
{
    // Check the error cases.
    binomial_coefficient_check_n_k_( n, k );

    // Since C(n, k) = C(n, n-k), we can shortcut.
    if( k > n - k ) {
        k = n - k;
    }
    assert( k <= n/2 );

    // We follow http://csharphelper.com/blog/2014/08/calculate-the-binomial-coefficient-n-choose-k-efficiently-in-c/
    // In short, C(n, k) = n/k * C(n-1, k-1), which we can continue until C(n-(k-1), 1) to get
    // a long chain product. Reading the factors from right to left, we always have the binomial
    // coefficients of smaller n,k, and use these as our intermediates to ensure that we don't
    // get an overflow here while multiplying them up.

    size_t result = 1;
    for( size_t i = 1; i <= k; i++)
    {
        // Multiply, with overflow check.
        assert( n > k - i );
        if( result >= std::numeric_limits<size_t>::max() / (n - (k - i)) ) {
            throw std::runtime_error(
                "Cannot compute binomial coefficient with n == " + std::to_string(n) +
                " and k == " + std::to_string(k) + " due to numerical overflow. " +
                "Use binomial_coefficient_approx() instead for large values."
            );
        }
        result *= n - (k - i);

        // As we are computing the product "backwards", we always have a valid intermediate value,
        // that is, the division by i is always an integer division (which we assert).
        assert( result % i == 0 );
        result /= i;
    }
    return result;
}

double log_binomial_coefficient( size_t n, size_t k )
{
    // Need that for the lenient case.
    static_assert(
        std::numeric_limits<double>::has_infinity,
        "IEC 559/IEEE 754 floating-point types required (does not have infinity)."
    );

    // Check the error cases.
    binomial_coefficient_check_n_k_( n, k );
    assert( k <= n );

    // We use a log factorial for the computation, see https://stackoverflow.com/a/37715980/4184258
    // Basically, what we are computing is C(n, k) = n!/((n-k)! * k!), which in log form is
    // log(n!) - log((n-k)!) - log(k!). We use a lookup table for these log factorial values,
    // and then finally only need to exponentiate them back to get the result.
    auto const lbc = log_factorial( n ) - log_factorial( n-k ) - log_factorial( k );
    assert( std::isfinite( lbc ) || std::isinf( lbc ));
    return lbc;
}

double log_binomial_distribution( size_t k, size_t n, double p )
{
    if( ! std::isfinite(p) || p < 0.0 || p > 1.0 ) {
        throw std::invalid_argument(
            "Cannot compute binomial distribution with p outside of [ 0, 1 ]"
        );
    }

    // We are computing coeff * std::pow( p, k ) * std::pow( 1.0 - p, n - k ).
    // In log space, the powers become multiplications of the exponent with the log of the base,
    // and multiplications become additions.

    // Get the log-space binomial coefficient. This already checks that k <= n, so we here only
    // assert, and then compute the two powers involved, also in log-space.
    double const log_coeff = log_binomial_coefficient( n, k );
    assert( k <= n );
    double const log_pow_1 = static_cast<double>(     k ) * std::log(       p );
    double const log_pow_2 = static_cast<double>( n - k ) * std::log( 1.0 - p );
    return log_coeff + log_pow_1 + log_pow_2;
}

} // namespace utils
} // namespace genesis