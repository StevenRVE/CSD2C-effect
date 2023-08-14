//
// Created by steve on 14-8-2023.
//

#include "filterCoefficients.hpp"

const int ANTI_ALIASING_LOW_QUALITY_TAPS = 45;
const float antiAliasingLowQuality[] =
{
    -0.01573471304144745,
    -0.016732469029538972,
    0.011000372979837745,
    0.0499323857388011,
    0.054270702860892736,
    0.016254903280061097,
    -0.013660350800598587,
    0.0014306536143222474,
    0.026416484263268203,
    0.011219119042410148,
    -0.02207878708125867,
    -0.013640608911050974,
    0.02568509481877424,
    0.023100983940582794,
    -0.026592163709257446,
    -0.03498918390575224,
    0.02839627203999566,
    0.05601600588597529,
    -0.029463720997028767,
    -0.10135426524989612,
    0.030245094753993014,
    0.31675539589620827,
    0.46958221951873397,
    0.31675539589620827,
    0.030245094753993014,
    -0.10135426524989612,
    -0.029463720997028767,
    0.05601600588597529,
    0.02839627203999566,
    -0.03498918390575224,
    -0.026592163709257446,
    0.023100983940582794,
    0.02568509481877424,
    -0.013640608911050974,
    -0.02207878708125867,
    0.011219119042410148,
    0.026416484263268203,
    0.0014306536143222474,
    -0.013660350800598587,
    0.016254903280061097,
    0.054270702860892736,
    0.0499323857388011,
    0.011000372979837745,
    -0.016732469029538972,
    -0.01573471304144745
};

const int ANTI_ALIASING_MIDDLE_QUALITY_TAPS = 93;
const float antiAliasingMidQuality[] =
{
    0.0032864066335093153,
    0.007838152648805913,
    0.008407844891968233,
    0.0021932623572421405,
    -0.004612476613860278,
    -0.003975097494446348,
    0.0018081210860810325,
    0.0028868704553597314,
    -0.0024492797239818735,
    -0.004693649347228158,
    0.0005165491111459939,
    0.004044418017594887,
    -0.0009737698970550195,
    -0.005929023106285263,
    -0.0012798129868477855,
    0.005307574271592658,
    0.0014056232425989632,
    -0.006889286933193938,
    -0.004141551474202373,
    0.0059203883984526706,
    0.00487961824788,
    -0.006839112440172429,
    -0.008058906617043695,
    0.0051402683845255814,
    0.009277080474702482,
    -0.00503278410520399,
    -0.012729186365651379,
    0.002220816664515147,
    0.014212450178126926,
    -0.0006813762858231276,
    -0.017734717009700442,
    -0.0038029240076832326,
    0.019191651067929028,
    0.007472293360886528,
    -0.022481075333984968,
    -0.014668119000140922,
    0.02362549206917194,
    0.022279055165033042,
    -0.026402940979382047,
    -0.035781607436876056,
    0.02694904924535295,
    0.055740729723263195,
    -0.02898564931175197,
    -0.10201483737564183,
    0.02873339254904847,
    0.31631446303226507,
    0.4701098782142389,
    0.31631446303226507,
    0.02873339254904847,
    -0.10201483737564183,
    -0.02898564931175197,
    0.055740729723263195,
    0.02694904924535295,
    -0.035781607436876056,
    -0.026402940979382047,
    0.022279055165033042,
    0.02362549206917194,
    -0.014668119000140922,
    -0.022481075333984968,
    0.007472293360886528,
    0.019191651067929028,
    -0.0038029240076832326,
    -0.017734717009700442,
    -0.0006813762858231276,
    0.014212450178126926,
    0.002220816664515147,
    -0.012729186365651379,
    -0.00503278410520399,
    0.009277080474702482,
    0.0051402683845255814,
    -0.008058906617043695,
    -0.006839112440172429,
    0.00487961824788,
    0.0059203883984526706,
    -0.004141551474202373,
    -0.006889286933193938,
    0.0014056232425989632,
    0.005307574271592658,
    -0.0012798129868477855,
    -0.005929023106285263,
    -0.0009737698970550195,
    0.004044418017594887,
    0.0005165491111459939,
    -0.004693649347228158,
    -0.0024492797239818735,
    0.0028868704553597314,
    0.0018081210860810325,
    -0.003975097494446348,
    -0.004612476613860278,
    0.0021932623572421405,
    0.008407844891968233,
    0.007838152648805913,
    0.0032864066335093153
};

const int ANTI_ALIASING_HIGH_QUALITY_TAPS = 123;
const float antiAliasingHighQuality[] =
{
    0.0011637116911058353,
    0.0012727834605425837,
    0.00003326771475551834,
    -0.0007821759552616762,
    -0.00016278432646737163,
    0.0009843250455916026,
    0.0002270175826819501,
    -0.0010350738486476557,
    -0.0005476837194464643,
    0.00122669224802417,
    0.0007931219756033254,
    -0.0012345932211190564,
    -0.0012372192543161525,
    0.0012971194870272256,
    0.0016299015493415744,
    -0.0011654839316042934,
    -0.0021703647369849827,
    0.0010153511990984296,
    0.0026549222493856372,
    -0.0006596958521153137,
    -0.0032279612597141756,
    0.0002258635823981301,
    0.0037198149413298445,
    0.00042733463022124474,
    -0.004221825646693807,
    -0.0011982501777913917,
    0.004592298383697777,
    0.0021909418231251545,
    -0.004882323754193164,
    -0.0033196458761431975,
    0.00496762609448633,
    0.004652718477449662,
    -0.0048706013780973525,
    -0.006112213073065573,
    0.00447861434991401,
    0.007737007510279108,
    -0.0037891947771048827,
    -0.009450494501274612,
    0.0026959491030568044,
    0.011266708896840274,
    -0.0011709854212064222,
    -0.013110239894983836,
    -0.0009038201930345418,
    0.014975185527725404,
    0.0036035501109639963,
    -0.01678922480722656,
    -0.00710799434698611,
    0.018534966962620494,
    0.011628617081257734,
    -0.020145193401144793,
    -0.017592120098599333,
    0.021599093457403448,
    0.025747571728661708,
    -0.02283887874711173,
    -0.03778024199867623,
    0.02384841298499067,
    0.0580462034148816,
    -0.02458336223910633,
    -0.10268921293705992,
    0.025039182912237484,
    0.3171612066257496,
    0.474812638948177,
    0.3171612066257496,
    0.025039182912237484,
    -0.10268921293705992,
    -0.02458336223910633,
    0.0580462034148816,
    0.02384841298499067,
    -0.03778024199867623,
    -0.02283887874711173,
    0.025747571728661708,
    0.021599093457403448,
    -0.017592120098599333,
    -0.020145193401144793,
    0.011628617081257734,
    0.018534966962620494,
    -0.00710799434698611,
    -0.01678922480722656,
    0.0036035501109639963,
    0.014975185527725404,
    -0.0009038201930345418,
    -0.013110239894983836,
    -0.0011709854212064222,
    0.011266708896840274,
    0.0026959491030568044,
    -0.009450494501274612,
    -0.0037891947771048827,
    0.007737007510279108,
    0.00447861434991401,
    -0.006112213073065573,
    -0.0048706013780973525,
    0.004652718477449662,
    0.00496762609448633,
    -0.0033196458761431975,
    -0.004882323754193164,
    0.0021909418231251545,
    0.004592298383697777,
    -0.0011982501777913917,
    -0.004221825646693807,
    0.00042733463022124474,
    0.0037198149413298445,
    0.0002258635823981301,
    -0.0032279612597141756,
    -0.0006596958521153137,
    0.0026549222493856372,
    0.0010153511990984296,
    -0.0021703647369849827,
    -0.0011654839316042934,
    0.0016299015493415744,
    0.0012971194870272256,
    -0.0012372192543161525,
    -0.0012345932211190564,
    0.0007931219756033254,
    0.00122669224802417,
    -0.0005476837194464643,
    -0.0010350738486476557,
    0.0002270175826819501,
    0.0009843250455916026,
    -0.00016278432646737163,
    -0.0007821759552616762,
    0.00003326771475551834,
    0.0012727834605425837,
    0.0011637116911058353
};