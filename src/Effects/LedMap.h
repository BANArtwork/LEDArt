#ifndef LEDMAP_H
#define LEDMAP_H

/**
 * @brief A class to handle mapping an LED in a strip 
 * to its physical location within an installation.
 */
class LedMap {

    public:

        LedMap(
            const int numLeds, 
            const int* xMap, 
            const int* yMap, 
            const int* zMap
        ) : 
            _numLeds { numLeds },
            _xMap { xMap },
            _yMap { yMap },
            _zMap { zMap } {}

        int getX(int index) {
            return get(_xMap, index);
        };

        int getY(int index) {
            return get(_yMap, index);
        };
        
        int getZ(int index) {
            return get(_zMap, index);
        };

    private:

        const int _numLeds;

        const int* _xMap;
        const int* _yMap;
        const int* _zMap;

        int get(const int* map, int index) {
            if (index < 0) return -1;
            if (index >= _numLeds) return -1;
            return map[index];
        };
};

#endif
