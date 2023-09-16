#include <iostream>

int main() {
    int pref[2] = {1, 0};
    
    int n;
    int bi;
    
    while(std::cin >> n) {
        long long ans = 0;
        int mask = 0;
        
        for(int i = 0; i < n; i++){
            std::cin >> bi;
            mask ^= bi;
            // Se a mascara é 0, mask ^ 1 é 1
            // Se a mascara é 1, mask ^ 1 é 0
            ans += pref[mask ^ 1];  

            pref[mask] += 1;
        }
        std::cout << ans << "\n";
    }
    return 0;
}