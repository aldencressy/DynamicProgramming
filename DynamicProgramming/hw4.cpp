#include <vector>
#include <utility>

using namespace std;

pair<vector<float>, vector<int> > WWWWW(vector<float> w, vector<float> p, int s, int t) {
    int n = w.size();

    float w_prime = 0.0;
    float quit = 0.0;
    float prev_quit = 0.0;
    float not_quit = 0.0;

    vector<float> c(n);
    vector<float> e(n);
    vector<int> q(n - 1);

    //compute c  and q values
    w_prime = w[t];
    for (int k = n - 1, i = n - 2; k > 0; --k, --i) {
        if (k == t) { w_prime = w[s]; }
        if (k == s) { w_prime = 0.0; }

        //prev_quit = w[k];
        quit = w[k - 1];

        if (k == n - 1) {
            c[k] = w[k];
            not_quit = (w[k] * p[k]) + (w_prime * (1 - p[k]));

            if (quit > not_quit) {
                q[i] = 0;
                c[k - 1] = quit;
            } else {
                q[i] = 1;
                c[k - 1] = not_quit;
            }
            continue;
        }

            not_quit = (c[k] * p[k]) + (w_prime * (1 - p[k]));

            if (quit > not_quit) {
                q[i] = 0;
                c[k - 1] = quit;
            } else {
                q[i] = 1;
                c[k - 1] = not_quit;
            }
    }

    float e1 = 0.0;
    float e2 = 0.0;

    w_prime = 0.0;
    for (int k = 1; k <= n; ++k) {
        if (k == s + 1) { w_prime = w[s]; }
        if (k == t + 1) { w_prime = w[t]; }

        e1 = w[k-1];
        e2 = (p[k] * c[k]) + ((1 - p[k]) * w_prime);

        e[k - 1] = max(e1, e2);
    }

    return make_pair(e, q);
}


pair<vector<vector<float> >, vector<vector<int> > > WWWWW_1(vector<float> w, vector<float> p, int s, int t) {
    vector<vector<float> > a;
    vector<vector<int> > b;

    a.resize(2);
    b.resize(2);

    int n = w.size();

    float w_prime = 0.0;
    float quit = 0.0;
    float prev_quit = 0.0;
    float not_quit = 0.0;

    float e1 = 0.0;
    float e2 = 0.0;
    float e3 = 0.0;
    float lprob = 0.0;
    float max1 = 0.0;

    vector<float> c(n);
    vector<float> e(n);
    vector<int> q(n - 1);

    a[0].resize(n);
    a[1].resize(n);

    b[0].resize(n - 1);
    b[1].resize(n - 1);

    w_prime = w[t];
    for (int k = n - 1, i = n - 2; k > 0; --k, --i) {
        if (k == t) { w_prime = w[s]; }
        if (k == s) { w_prime = 0.0; }

        //prev_quit = w[k];
        quit = w[k - 1];

        if (k == n - 1) {
            c[k] = w[k];
            not_quit = (w[k] * p[k]) + (w_prime * (1 - p[k]));

            if (quit > not_quit) {
                b[0][i] = 0;
                c[k - 1] = quit;
            } else {
                b[0][i] = 1;
                c[k - 1] = not_quit;
            }
            continue;
        }

        not_quit = (c[k] * p[k]) + (w_prime * (1 - p[k]));

        if (quit > not_quit) {
            b[0][i] = 0;
            c[k - 1] = quit;
        } else {
            b[0][i] = 1;
            c[k - 1] = not_quit;
        }
    }


    w_prime = 0.0;
    for (int k = 1; k <= n; ++k) {
        if (k == s + 1) { w_prime = w[s]; }
        if (k == t + 1) { w_prime = w[t]; }

        e1 = w[k-1];
        e2 = (p[k] * c[k]) + ((1 - p[k]) * w_prime);

        a[0][k - 1] = max(e1, e2);
    }


    float lifeline = 0.0;
    vector<float> c2(n);
    w_prime = w[t];


    for (int k = n - 1, i = n - 2; k > 0; --k, --i) {
        if (k == t) { w_prime = w[s]; }
        if (k == s) { w_prime = 0.0; }

        quit = w[k - 1];
        prev_quit = w[k];

        if (k == n - 1) {
            c2[k] = w[k];
            not_quit = (w[k] * p[k]) + (w_prime * (1 - p[k]));
            lifeline = c[k] * (0.5 + p[k] / 2.0) + (1 - (0.5 + p[k] / 2.0)) * w_prime;
            //lifeline = c[k] * (0.6) + (1 - (0.6)) * w_prime;

            if (quit > not_quit && quit > lifeline) {
                c2[k - 1] = quit;
                b[1][i] = 0;
                continue;
            }

            if (not_quit > quit && not_quit > lifeline) {
                c2[k - 1] = not_quit;
                b[1][i] = 1;
                continue;
            }
            else {
                c2[k -1] = lifeline;
                b[1][i] = 2;
                continue;
            }
        }

        if (lifeline > prev_quit && lifeline > not_quit) {
            not_quit = (lifeline * p[k]) + (w_prime * (1 - p[k]));
            lifeline = c[k] * (0.5 + p[k] / 2.0) + (1 - (0.5 + p[k] / 2.0)) * w_prime;
            //lifeline = c[k] * (0.6) + (1 - (0.6)) * w_prime;

            if (quit > not_quit && quit > lifeline) {
                c2[k - 1] = quit;
                b[1][i] = 0;
                continue;
            }

            if (not_quit > quit && not_quit > lifeline) {
                c2[k - 1] = not_quit;
                b[1][i] = 1;
                continue;
            }
            else {
                c2[k -1] = lifeline;
                b[1][i] = 2;
                continue;
            }

        }

        if (not_quit > lifeline && not_quit > prev_quit) {

            not_quit = (not_quit * p[k]) + (w_prime * (1 - p[k]));
            lifeline = c[k] * (0.5 + p[k] / 2.0) + (1 - (0.5 + p[k] / 2.0)) * w_prime;
            //lifeline = c[k] * (0.6) + (1 - (0.6)) * w_prime;


            if (quit > not_quit && quit > lifeline) {
                c2[k - 1] = quit;
                b[1][i] = 0;
                continue;
            }

            if (not_quit > quit && not_quit > lifeline) {
                c2[k - 1] = not_quit;
                b[1][i] = 1;
                continue;
            }
            else {
                c2[k - 1] = lifeline;
                b[1][i] = 2;
                continue;
            }

        } else {
            not_quit = (quit * p[k]) + (w_prime * (1 - p[k]));
            lifeline = c[k] * (0.5 + p[k] / 2.0) + (1 - (0.5 + p[k] / 2.0)) * w_prime;
            //lifeline = c[k] * (0.6) + (1 - (0.6)) * w_prime;

            if (quit > not_quit && quit > lifeline) {
                c2[k - 1] = quit;
                b[1][i] = 0;
                continue;
            }

            if (not_quit > quit && not_quit > lifeline) {
                c2[k - 1] = not_quit;
                b[1][i] = 1;
                continue;
            }
            else {
                c2[k - 1] = lifeline;
                b[1][i] = 2;
                continue;
            }

        }

    }


    w_prime = 0.0;
    for (int k = 1; k <= n; ++k) {
        if (k == s + 1) { w_prime = w[s]; }
        if (k == t + 1) { w_prime = w[t]; }

        lprob = (0.5 + p[k] / 2.0);
        //lprob = 0.6;
        e1 = w[k - 1];
        e2 = (p[k] * c2[k]) + ((1 - p[k]) * w_prime);
        e3 = max(p[k], lprob) * c[k] + (1 - max(p[k], lprob)) * w_prime;


        max1 = max(e1, e2);

        a[1][k - 1] = max(max1, e3);
    }

    return make_pair(a, b);
}






pair<vector<vector<float> >, vector<vector<int> > > WWWWW_2(vector<float> w, vector<float> p, int s, int t) {

    vector<vector<float> > a;
    vector<vector<int> > b;

    a.resize(4);
    b.resize(4);

    int n = w.size();

    float w_prime = 0.0;
    float quit = 0.0;
    float prev_quit = 0.0;
    float not_quit = 0.0;

    float e1 = 0.0;
    float e2 = 0.0;
    float e3 = 0.0;
    float lprob = 0.0;
    float max1 = 0.0;

    vector<float> c(n);
    vector<float> e(n);
    vector<int> q(n - 1);

    a[0].resize(n);
    a[1].resize(n);
    a[2].resize(n);
    a[3].resize(n);

    b[0].resize(n - 1);
    b[1].resize(n - 1);
    b[2].resize(n - 1);
    b[3].resize(n - 1);

    w_prime = w[t];
    for (int k = n - 1, i = n - 2; k > 0; --k, --i) {
        if (k == t) { w_prime = w[s]; }
        if (k == s) { w_prime = 0.0; }

        //prev_quit = w[k];
        quit = w[k - 1];

        if (k == n - 1) {
            c[k] = w[k];
            not_quit = (w[k] * p[k]) + (w_prime * (1 - p[k]));

            if (quit > not_quit) {
                b[0][i] = 0;
                c[k - 1] = quit;
            } else {
                b[0][i] = 1;
                c[k - 1] = not_quit;
            }
            continue;
        }

        not_quit = (c[k] * p[k]) + (w_prime * (1 - p[k]));

        if (quit > not_quit) {
            b[0][i] = 0;
            c[k - 1] = quit;
        } else {
            b[0][i] = 1;
            c[k - 1] = not_quit;
        }
    }

    w_prime = 0.0;
    for (int k = 1; k <= n; ++k) {
        if (k == s + 1) { w_prime = w[s]; }
        if (k == t + 1) { w_prime = w[t]; }

        e1 = w[k-1];
        e2 = (p[k] * c[k]) + ((1 - p[k]) * w_prime);

        a[0][k - 1] = max(e1, e2);
    }

    float lifeline = 0.0;
    vector<float> c2(n);
    w_prime = w[t];

    for (int k = n - 1, i = n - 2; k > 0; --k, --i) {
        if (k == t) { w_prime = w[s]; }
        if (k == s) { w_prime = 0.0; }

        quit = w[k - 1];
        prev_quit = w[k];

        if (k == n - 1) {
            c2[k] = w[k];
            not_quit = (w[k] * p[k]) + (w_prime * (1 - p[k]));
            lifeline = c[k] * (0.5 + p[k] / 2.0) + (1 - (0.5 + p[k] / 2.0)) * w_prime;

            if (quit > not_quit && quit > lifeline) {
                c2[k - 1] = quit;
                b[1][i] = 0;
                continue;
            }

            if (not_quit > quit && not_quit > lifeline) {
                c2[k - 1] = not_quit;
                b[1][i] = 1;
                continue;
            }
            else {
                c2[k -1] = lifeline;
                b[1][i] = 2;
                continue;
            }
        }

        if (lifeline > prev_quit && lifeline > not_quit) {
            not_quit = (lifeline * p[k]) + (w_prime * (1 - p[k]));
            lifeline = c[k] * (0.5 + p[k] / 2.0) + (1 - (0.5 + p[k] / 2.0)) * w_prime;

            if (quit > not_quit && quit > lifeline) {
                c2[k - 1] = quit;
                b[1][i] = 0;
                continue;
            }

            if (not_quit > quit && not_quit > lifeline) {
                c2[k - 1] = not_quit;
                b[1][i] = 1;
                continue;
            }
            else {
                c2[k -1] = lifeline;
                b[1][i] = 2;
                continue;
            }

        }

        if (not_quit > lifeline && not_quit > prev_quit) {

            not_quit = (not_quit * p[k]) + (w_prime * (1 - p[k]));
            lifeline = c[k] * (0.5 + p[k] / 2.0) + (1 - (0.5 + p[k] / 2.0)) * w_prime;

            if (quit > not_quit && quit > lifeline) {
                c2[k - 1] = quit;
                b[1][i] = 0;
                continue;
            }

            if (not_quit > quit && not_quit > lifeline) {
                c2[k - 1] = not_quit;
                b[1][i] = 1;
                continue;
            }
            else {
                c2[k - 1] = lifeline;
                b[1][i] = 2;
                continue;
            }

        } else {
            not_quit = (quit * p[k]) + (w_prime * (1 - p[k]));
            lifeline = c[k] * (0.5 + p[k] / 2.0) + (1 - (0.5 + p[k] / 2.0)) * w_prime;

            if (quit > not_quit && quit > lifeline) {
                c2[k - 1] = quit;
                b[1][i] = 0;
                continue;
            }

            if (not_quit > quit && not_quit > lifeline) {
                c2[k - 1] = not_quit;
                b[1][i] = 1;
                continue;
            }
            else {
                c2[k - 1] = lifeline;
                b[1][i] = 2;
                continue;
            }

        }

    }

    w_prime = 0.0;
    for (int k = 1; k <= n; ++k) {
        if (k == s + 1) { w_prime = w[s]; }
        if (k == t + 1) { w_prime = w[t]; }

        lprob = (0.5 + p[k] / 2.0);
        e1 = w[k - 1];
        e2 = (p[k] * c2[k]) + ((1 - p[k]) * w_prime);
        e3 = max(p[k], lprob) * c[k] + (1 - max(p[k], lprob)) * w_prime;

        max1 = max(e1, e2);

        a[1][k - 1] = max(max1, e3);
    }

    vector<float> c3(n);
    w_prime = w[t];

    for (int k = n - 1, i = n - 2; k > 0; --k, --i) {
        if (k == t) { w_prime = w[s]; }
        if (k == s) { w_prime = 0.0; }

        quit = w[k - 1];
        prev_quit = w[k];

        if (k == n - 1) {
            c3[k] = w[k];
            not_quit = (w[k] * p[k]) + (w_prime * (1 - p[k]));
            lifeline = w[k] - (k - 1)*10;

            if (quit > not_quit && quit > lifeline) {
                c3[k - 1] = quit;
                b[2][i] = 0;
                continue;
            }

            if (not_quit > quit && not_quit > lifeline) {
                c3[k - 1] = not_quit;
                b[2][i] = 1;
                continue;
            }
            else {
                c3[k -1] = lifeline;
                b[2][i] = 3;
                continue;
            }
        }

        if (lifeline > prev_quit && lifeline > not_quit) {
            not_quit = (lifeline * p[k]) + (w_prime * (1 - p[k]));
            lifeline =  w[k] - (k - 1)*10;

            if (quit >= not_quit && quit > lifeline) {
                c3[k - 1] = quit;
                b[2][i] = 0;
                continue;
            }

            if (not_quit > quit && not_quit > lifeline) {
                c3[k - 1] = not_quit;
                b[2][i] = 1;
                continue;
            }
            else {
                c3[k -1] = lifeline;
                b[2][i] = 3;
                continue;
            }

        }

        if (not_quit > lifeline && not_quit > prev_quit) {

            not_quit = (not_quit * p[k]) + (w_prime * (1 - p[k]));
            lifeline = w[k] - (k - 1)*10;

            if (quit >= not_quit && quit > lifeline) {
                c3[k - 1] = quit;
                b[2][i] = 0;
                continue;
            }

            if (not_quit > quit && not_quit > lifeline) {
                c3[k - 1] = not_quit;
                b[2][i] = 1;
                continue;
            }
            else {
                c3[k - 1] = lifeline;
                b[2][i] = 3;
                continue;
            }

        } else {
            not_quit = (c3[k] * p[k]) + (w_prime * (1 - p[k]));
            lifeline = w[k] - (k - 1)*10;

            if (quit >= not_quit && quit > lifeline) {
                c3[k - 1] = quit;
                b[2][i] = 0;
                continue;
            }

            if (not_quit > quit && not_quit > lifeline) {
                c3[k - 1] = not_quit;
                b[2][i] = 1;
                continue;
            }
            else {
                c3[k - 1] = lifeline;
                b[2][i] = 3;
                continue;
            }

        }

    }
    w_prime = 0.0;


    for (int k = 1; k <= n; ++k) {
        if (k == s + 1) { w_prime = w[s]; }
        if (k == t + 1) { w_prime = w[t]; }

        //lprob = 1;
        e1 = w[k - 1];
        e2 = (p[k] * c3[k]) + ((1 - p[k]) * w_prime);
        e3 = w[k] - (k - 1)*10;

        max1 = max(e1, e2);

        a[2][k - 1] = max(max1, e3);
    }

    float lifeline2 = 0.0;
    vector<float> c4(n);
    w_prime = w[t];

    for (int k = n - 1, i = n - 2; k > 0; --k, --i) {
        if (k == t) { w_prime = w[s]; }
        if (k == s) { w_prime = 0.0; }

        quit = w[k - 1];
        prev_quit = w[k];

        if (k == n - 1) {
            c4[k] = w[k];
            not_quit = (w[k] * p[k]) + (w_prime * (1 - p[k]));
            lifeline = w[k] - (k - 1)*10;
            lifeline2 = c3[k] * (0.5 + p[k] / 2.0) + (1 - (0.5 + p[k] / 2.0)) * w_prime;

            if (quit > not_quit && quit > lifeline && quit > lifeline2) {
                c4[k - 1] = quit;
                b[3][i] = 0;
                continue;
            }

            if (not_quit > quit && not_quit > lifeline && not_quit > lifeline2) {
                c4[k - 1] = not_quit;
                b[3][i] = 1;
                continue;
            }

            if (lifeline2 > quit && lifeline2 > not_quit && lifeline2 > lifeline) {
                c4[k - 1] = lifeline2;
                b[3][i] = 2;
                continue;
            }

            else {
                c4[k -1] = lifeline;
                b[3][i] = 3;
                continue;
            }
        }

        if (lifeline > prev_quit && lifeline > not_quit && lifeline > lifeline2) {
            not_quit = (lifeline * p[k]) + (w_prime * (1 - p[k]));
            lifeline =  w[k] - (k - 1)*10;
            lifeline2 = c3[k] * (0.5 + p[k] / 2.0) + (1 - (0.5 + p[k] / 2.0)) * w_prime;

            if (quit >= not_quit && quit > lifeline && quit > lifeline2) {
                c4[k - 1] = quit;
                b[3][i] = 0;
                continue;
            }

            if (not_quit > quit && not_quit > lifeline && not_quit > lifeline2) {
                c4[k - 1] = not_quit;
                b[3][i] = 1;
                continue;
            }

            if (lifeline2 > quit && lifeline2 > not_quit && lifeline2 > lifeline) {
                c4[k - 1] = lifeline2;
                b[3][i] = 2;
                continue;
            }
            else {
                c4[k -1] = lifeline;
                b[3][i] = 3;
                continue;
            }

        }

        if (not_quit > lifeline && not_quit > prev_quit && not_quit > lifeline2) {

            not_quit = (not_quit * p[k]) + (w_prime * (1 - p[k]));
            lifeline = w[k] - (k - 1)*10;
            lifeline2 = c3[k] * (0.5 + p[k] / 2.0) + (1 - (0.5 + p[k] / 2.0)) * w_prime;

            if (quit >= not_quit && quit > lifeline && quit > lifeline2) {
                c4[k - 1] = quit;
                b[3][i] = 0;
                continue;
            }

            if (not_quit > quit && not_quit > lifeline && not_quit > lifeline2) {
                c4[k - 1] = not_quit;
                b[3][i] = 1;
                continue;
            }

            if (lifeline2 > quit && lifeline2 > not_quit && lifeline2 > lifeline) {
                c4[k - 1] = lifeline2;
                b[3][i] = 2;
                continue;
            }
            else {
                c4[k - 1] = lifeline;
                b[3][i] = 3;
                continue;
            }

        }

        if (lifeline2 > lifeline && lifeline2 > prev_quit && lifeline2 > not_quit) {

            not_quit = (lifeline2 * p[k]) + (w_prime * (1 - p[k]));
            lifeline = w[k] - (k - 1)*10;
            lifeline2 = c3[k] * (0.5 + p[k] / 2.0) + (1 - (0.5 + p[k] / 2.0)) * w_prime;

            if (quit >= not_quit && quit > lifeline && quit > lifeline2) {
                c4[k - 1] = quit;
                b[3][i] = 0;
                continue;
            }

            if (not_quit > quit && not_quit > lifeline && not_quit > lifeline2) {
                c4[k - 1] = not_quit;
                b[3][i] = 1;
                continue;
            }

            if (lifeline2 > quit && lifeline2 > not_quit && lifeline2 > lifeline) {
                c4[k - 1] = lifeline2;
                b[3][i] = 2;
                continue;
            }
            else {
                c4[k - 1] = lifeline;
                b[3][i] = 3;
                continue;
            }

        }

        else {
            not_quit = (c4[k] * p[k]) + (w_prime * (1 - p[k]));
            lifeline = w[k] - (k - 1)*10;
            lifeline2 = c3[k] * (0.5 + p[k] / 2.0) + (1 - (0.5 + p[k] / 2.0)) * w_prime;

            if (quit >= not_quit && quit > lifeline && quit > lifeline2) {
                c4[k - 1] = quit;
                b[3][i] = 0;
                continue;
            }

            if (not_quit > quit && not_quit > lifeline && not_quit > lifeline2) {
                c4[k - 1] = not_quit;
                b[3][i] = 1;
                continue;
            }

            if (lifeline2 > quit && lifeline2 > not_quit && lifeline2 > lifeline) {
                c4[k - 1] = lifeline2;
                b[3][i] = 2;
                continue;
            }
            else {
                c4[k - 1] = lifeline;
                b[3][i] = 3;
                continue;
            }

        }

    }

    float lprob1 = 0.0;
    float e4 = 0.0;
    float max2 = 0.0;

    for (int k = 1; k <= n; ++k) {
        if (k == s + 1) { w_prime = w[s]; }
        if (k == t + 1) { w_prime = w[t]; }

        lprob1 = (0.5 + p[k] / 2.0);

        e1 = w[k - 1];
        e2 = (p[k] * c4[k]) + ((1 - p[k]) * w_prime);
        e3 = w[k] - (k - 1)*10;
        e4 = max(p[k], lprob1) * c3[k] + (1 - max(p[k], lprob1)) * w_prime;

        max1 = max(e1, e2);
        max2 = max(e3, e4);
        a[3][k - 1] = max(max1, max2);
    }
    return make_pair(a, b);
}





 
