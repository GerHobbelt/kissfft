#include "kiss_fft.h"

#define xstr(s) str(s)
#define str(s) #s

static
double snr_compare( kiss_fft_cpx * test_vec_out,kiss_fft_cpx * testbuf, int n)
{
    int k;
    double sigpow,noisepow,err,snr,scale=0;
    sigpow = noisepow = .000000000000000000000000000001; 

    for (k=0;k<n;++k) {
        sigpow += test_vec_out[k].r * test_vec_out[k].r + 
                  test_vec_out[k].i * test_vec_out[k].i;
        err = test_vec_out[k].r - testbuf[k].r;
        noisepow += err * err;
        err = test_vec_out[k].i - testbuf[k].i;
        noisepow += err * err;

        if (test_vec_out[k].r)
            scale += testbuf[k].r / test_vec_out[k].r;
    }
    snr = 10*log10( sigpow / noisepow );
    scale /= n;
    if (snr<10)
        printf( "\npoor snr, try a scaling factor %f\n" , scale );
    return snr;
}

int main(void) { int exit_code=0;

#define NFFT 10
    {
        double snr;
        kiss_fft_cpx test_vec_in[NFFT] = { {7530 ,-23557 },{-3817 ,-3583 },{-9845 ,-13410 },{17935 ,-21771 },{178 ,15797 },{18218 ,-23231 },{12641 ,-13884 },{-11860 ,-14108 },{32461 ,4775 },{31395 ,16528 }};
        kiss_fft_cpx test_vec_out[NFFT] = {{9483.600000000000363797880709171295166015625 ,-7644.4000000000005456968210637569427490234375 },{-1259.407204482226234176778234541416168212890625 ,5693.92644551078046788461506366729736328125 },{-3851.982954783657987718470394611358642578125 ,5783.144615476741819293238222599029541015625 },{-433.6047861735388551096548326313495635986328125 ,1221.190364624483891020645387470722198486328125 },{-1732.78395538423364996560849249362945556640625 ,-12776.4556167024784372188150882720947265625 },{-890.5999999999954752638586796820163726806640625 ,1588.600000000002864908310584723949432373046875 },{2119.2133681536079166107811033725738525390625 ,-1736.335781303392650443129241466522216796875 },{-5292.5415986136367791914381086826324462890625 ,-6376.3772599635776714421808719635009765625 },{6855.9535420142847215174697339534759521484375 ,-7019.9532174708701859344728291034698486328125 },{2532.15358926939734374172985553741455078125 ,-2290.3395501716904618660919368267059326171875 }};
        kiss_fft_cpx testbuf[NFFT];
        kiss_fft_cfg  cfg = kiss_fft_alloc(NFFT,0,0,0);

        kiss_fft(cfg,test_vec_in,testbuf);
        snr = snr_compare(test_vec_out,testbuf,NFFT);
        printf("DATATYPE=" xstr(kiss_fft_scalar) ", FFT n=%d, inverse=%d, snr = %g dB\n",NFFT,0,snr);
        if (snr<30)
            exit_code++;
        free(cfg);
    }
#undef NFFT    

#define NFFT 10
    {
        double snr;
        kiss_fft_cpx test_vec_in[NFFT] = { {8091 ,11849 },{-5357 ,-12270 },{28451 ,-12710 },{10987 ,-20331 },{-815 ,11764 },{10665 ,9843 },{13951 ,14588 },{-17884 ,1562 },{-14792 ,-13666 },{27948 ,11003 }};
        kiss_fft_cpx test_vec_out[NFFT] = {{6124.5 ,163.19999999999998863131622783839702606201171875 },{4667.911102893483985099010169506072998046875 ,1764.01321093053729782695882022380828857421875 },{3034.3526714159224866307340562343597412109375 ,5678.2776405304093714221380650997161865234375 },{-961.2646939679365232223062776029109954833984375 ,-7141.0850834791808665613643825054168701171875 },{2569.21337228864149437868036329746246337890625 ,-3711.8298559396635027951560914516448974609375 },{852.6999999999998181010596454143524169921875 ,2201.79999999999199644662439823150634765625 },{-4180.848820702709417673759162425994873046875 ,1201.277152949158107730909250676631927490234375 },{-3463.91710966937398552545346319675445556640625 ,10480.0716122495578019879758358001708984375 },{1830.78277699814543666434474289417266845703125 ,7515.075062460096887662075459957122802734375 },{-2382.42929925617272601812146604061126708984375 ,-6301.7997397009048654581420123577117919921875 }};
        kiss_fft_cpx testbuf[NFFT];
        kiss_fft_cfg  cfg = kiss_fft_alloc(NFFT,1,0,0);

        kiss_fft(cfg,test_vec_in,testbuf);
        snr = snr_compare(test_vec_out,testbuf,NFFT);
        printf("DATATYPE=" xstr(kiss_fft_scalar) ", FFT n=%d, inverse=%d, snr = %g dB\n",NFFT,1,snr);
        if (snr<30)
            exit_code++;
        free(cfg);
    }
#undef NFFT    

#define NFFT 12
    {
        double snr;
        kiss_fft_cpx test_vec_in[NFFT] = { {14304 ,11200 },{-4382 ,-25943 },{-16381 ,-19769 },{14993 ,-14179 },{-13420 ,-12249 },{32243 ,-8509 },{4444 ,-14413 },{9963 ,6124 },{6201 ,-31726 },{-14697 ,14887 },{-1091 ,-756 },{-5908 ,8328 }};
        kiss_fft_cpx test_vec_out[NFFT] = {{2189.0833333333330301684327423572540283203125 ,-7250.416666666666060336865484714508056640625 },{-7820.461150809327591559849679470062255859375 ,1065.770497656800216645933687686920166015625 },{-298.73538926515129787730984389781951904296875 ,2712.64460052931963218725286424160003662109375 },{22.91666666666666429819088079966604709625244140625 ,670.583333333333257542108185589313507080078125 },{2646.4842426786844953312538564205169677734375 ,5122.4372711610531041515059769153594970703125 },{-310.2888491906775243478477932512760162353515625 ,-1774.9371643234626390039920806884765625 },{-3179.5833333333330301684327423572540283203125 ,-4035.0833333333330301684327423572540283203125 },{8676.35044870199271827004849910736083984375 ,10196.198314262959684128873050212860107421875 },{-74.567576012022215081742615438997745513916015625 ,1501.729395505611364569631405174732208251953125 },{3329.25 ,-310.08333333333331438552704639732837677001953125 },{8091.318722598489330266602337360382080078125 ,342.18873280401140846151974983513355255126953125 },{1032.232884631344631998217664659023284912109375 ,2958.96835240370501196593977510929107666015625 }};
        kiss_fft_cpx testbuf[NFFT];
        kiss_fft_cfg  cfg = kiss_fft_alloc(NFFT,0,0,0);

        kiss_fft(cfg,test_vec_in,testbuf);
        snr = snr_compare(test_vec_out,testbuf,NFFT);
        printf("DATATYPE=" xstr(kiss_fft_scalar) ", FFT n=%d, inverse=%d, snr = %g dB\n",NFFT,0,snr);
        if (snr<30)
            exit_code++;
        free(cfg);
    }
#undef NFFT    

#define NFFT 12
    {
        double snr;
        kiss_fft_cpx test_vec_in[NFFT] = { {-7942 ,22308 },{8725 ,15501 },{-6876 ,-6752 },{67 ,-10584 },{-12372 ,30673 },{-26042 ,-29466 },{11448 ,11476 },{13084 ,19679 },{3191 ,2468 },{32168 ,13655 },{20585 ,7544 },{-15705 ,-18481 }};
        kiss_fft_cpx test_vec_out[NFFT] = {{1694.25 ,4835.0833333333330301684327423572540283203125 },{1417.254376882139013105188496410846710205078125 ,-6346.3618374050865895696915686130523681640625 },{-6345.4290045122252195142209529876708984375 ,4341.6783590580380405299365520477294921875 },{-4279.6666666666669698315672576427459716796875 ,5048.8333333333330301684327423572540283203125 },{-5445.9199522192930089659057557582855224609375 ,7634.7567347625854381476528942584991455078125 },{2561.99562311786530699464492499828338623046875 ,-1118.888162594913637803983874619007110595703125 },{-355.25 ,6451.0833333333330301684327423572540283203125 },{-4749.0122670884293256676755845546722412109375 ,-754.034324665195526904426515102386474609375 },{12686.919952219299375428818166255950927734375 ,-3256.0900680959093733690679073333740234375 },{-2767 ,2148 },{-481.57099548778302278151386417448520660400390625 ,-3114.51169239137880140333436429500579833984375 },{-1878.571066244906205611187033355236053466796875 ,6438.4509913318588587571866810321807861328125 }};
        kiss_fft_cpx testbuf[NFFT];
        kiss_fft_cfg  cfg = kiss_fft_alloc(NFFT,1,0,0);

        kiss_fft(cfg,test_vec_in,testbuf);
        snr = snr_compare(test_vec_out,testbuf,NFFT);
        printf("DATATYPE=" xstr(kiss_fft_scalar) ", FFT n=%d, inverse=%d, snr = %g dB\n",NFFT,1,snr);
        if (snr<30)
            exit_code++;
        free(cfg);
    }
#undef NFFT    

#define NFFT 14
    {
        double snr;
        kiss_fft_cpx test_vec_in[NFFT] = { {31087 ,59 },{27270 ,-7729 },{-16541 ,22446 },{-695 ,1554 },{24213 ,-18144 },{25885 ,-22447 },{-27719 ,-15964 },{31484 ,5363 },{7029 ,-32501 },{21358 ,28443 },{-9333 ,9025 },{6911 ,-48 },{13481 ,-13662 },{30348 ,22381 }};
        kiss_fft_cpx test_vec_out[NFFT] = {{11769.85714285714129800908267498016357421875 ,-1516 },{-393.3841187594547363914898596704006195068359375 ,4765.7340318322594612254761159420013427734375 },{8399.050295731232836260460317134857177734375 ,1049.108638399316305367392487823963165283203125 },{4863.8743878736522674444131553173065185546875 ,4844.6122307337254824233241379261016845703125 },{-5572.7980797887203152640722692012786865234375 ,-5939.78520266990017262287437915802001953125 },{-3794.80592902438729652203619480133056640625 ,-3017.2552588767221095622517168521881103515625 },{-575.294942150381984902196563780307769775390625 ,3297.3807863236825141939334571361541748046875 },{-8596.000000000005456968210637569427490234375 ,-5446.9999999999863575794734060764312744140625 },{8025.776361990603618323802947998046875 ,3387.7179954000412180903367698192596435546875 },{-2752.87451878362071511219255626201629638671875 ,-2083.37330774109204867272637784481048583984375 },{9529.85241126593973604030907154083251953125 ,5208.8070042008430391433648765087127685546875 },{4814.91445521927016670815646648406982421875 ,-4901.1303107252106201485730707645416259765625 },{-290.94318990580876516105490736663341522216796875 ,-2776.22922165396812488324940204620361328125 },{5659.7757234745049572666175663471221923828125 ,3186.41261477700800242018885910511016845703125 }};
        kiss_fft_cpx testbuf[NFFT];
        kiss_fft_cfg  cfg = kiss_fft_alloc(NFFT,0,0,0);

        kiss_fft(cfg,test_vec_in,testbuf);
        snr = snr_compare(test_vec_out,testbuf,NFFT);
        printf("DATATYPE=" xstr(kiss_fft_scalar) ", FFT n=%d, inverse=%d, snr = %g dB\n",NFFT,0,snr);
        if (snr<30)
            exit_code++;
        free(cfg);
    }
#undef NFFT    

#define NFFT 14
    {
        double snr;
        kiss_fft_cpx test_vec_in[NFFT] = { {-15159 ,-6148 },{-3120 ,-17757 },{28699 ,-874 },{19440 ,-16936 },{7712 ,-14279 },{-14078 ,-30468 },{-26763 ,-11349 },{17989 ,15372 },{-5469 ,-17344 },{-1699 ,-18576 },{28789 ,21810 },{11302 ,-15900 },{-12786 ,-27484 },{-30037 ,-5977 }};
        kiss_fft_cpx test_vec_out[NFFT] = {{344.28571428571427759379730559885501861572265625 ,-10422.142857142856883001513779163360595703125 },{835.194140787136575454496778547763824462890625 ,-39.71176755605431907270030933432281017303466796875 },{-9814.430976168872803100384771823883056640625 ,8531.513627975500639877282083034515380859375 },{-6291.8781575584898746456019580364227294921875 ,1024.372103878513371455483138561248779296875 },{8615.963474879268687800504267215728759765625 ,5402.8440694244009137037210166454315185546875 },{-702.2730063069351444937638007104396820068359375 ,-6798.457096024512793519534170627593994140625 },{3607.5345606706223406945355236530303955078125 ,1508.467596938962969943531788885593414306640625 },{373.28571428570438683891552500426769256591796875 ,2469.57142857143799119512550532817840576171875 },{3087.5044042293202437576837837696075439453125 ,467.3366070345840626032440923154354095458984375 },{-5699.389856636798867839388549327850341796875 ,-2570.7377979547236463986337184906005859375 },{-161.21857047615725377909257076680660247802734375 ,5289.939913700656688888557255268096923828125 },{-2038.815773703344575551454909145832061767578125 ,-3008.02179792261131296982057392597198486328125 },{-4264.6386074198662754497490823268890380859375 ,-6165.9589579312641944852657616138458251953125 },{-3050.12306086726630383054725825786590576171875 ,-1837.015072992040586541406810283660888671875 }};
        kiss_fft_cpx testbuf[NFFT];
        kiss_fft_cfg  cfg = kiss_fft_alloc(NFFT,1,0,0);

        kiss_fft(cfg,test_vec_in,testbuf);
        snr = snr_compare(test_vec_out,testbuf,NFFT);
        printf("DATATYPE=" xstr(kiss_fft_scalar) ", FFT n=%d, inverse=%d, snr = %g dB\n",NFFT,1,snr);
        if (snr<30)
            exit_code++;
        free(cfg);
    }
#undef NFFT    


    return exit_code;
}

