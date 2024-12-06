import React, { useState, useEffect } from 'react';
import { Slider } from '@/components/ui/slider';
import { Card, CardHeader, CardTitle, CardContent } from '@/components/ui/card';

const GarageParkingAssistant = () => {
  const [distance, setDistance] = useState(2.5);
  const [isWarningState, setIsWarningState] = useState(false);
  const [warningBlink, setWarningBlink] = useState(false);

  // Constants from the configuration
  const MIN_DISTANCE = 0.5;
  const BUFFER_DISTANCE = 0.1;
  const MAX_DISTANCE = 5.0;
  const NUM_LEDS = 60;
  
  // Calculate boundaries
  const minSafe = MIN_DISTANCE - BUFFER_DISTANCE;
  const maxSafe = MIN_DISTANCE + BUFFER_DISTANCE;

  // Warning blink effect
  useEffect(() => {
    let interval;
    if (isWarningState) {
      interval = setInterval(() => {
        setWarningBlink(prev => !prev);
      }, 500);
    }
    return () => clearInterval(interval);
  }, [isWarningState]);

  // Calculate LED colors based on distance
  const calculateLEDs = () => {
    if (distance < minSafe) {
      return Array(NUM_LEDS).fill(warningBlink ? '#ff0000' : '#000000');
    }

    const leds = Array(NUM_LEDS).fill('#000000');
    const center = Math.floor(NUM_LEDS / 2);

    if (distance <= maxSafe) {
      return Array(NUM_LEDS).fill('#ff0000');
    } else if (distance >= MAX_DISTANCE) {
      return Array(NUM_LEDS).fill('#00ff00');
    } else {
      const distanceRatio = (distance - maxSafe) / (MAX_DISTANCE - maxSafe);
      const ledsToLight = Math.max(2, Math.ceil(NUM_LEDS * distanceRatio));
      const halfLeds = Math.floor(ledsToLight / 2);
      
      const red = Math.floor(255 * (1 - distanceRatio));
      const green = Math.floor(255 * distanceRatio);
      const color = `#${red.toString(16).padStart(2, '0')}${green.toString(16).padStart(2, '0')}00`;
      
      for (let i = 0; i < halfLeds; i++) {
        leds[center + i] = color;
        leds[center - 1 - i] = color;
      }
    }
    return leds;
  };

  // Update warning state when distance changes
  useEffect(() => {
    setIsWarningState(distance < minSafe);
  }, [distance]);

  const leds = calculateLEDs();

  return (
    <Card className="w-full max-w-2xl">
      <CardHeader>
        <CardTitle>Garage Parking Assistant Simulator</CardTitle>
      </CardHeader>
      <CardContent className="space-y-6">
        <div className="flex items-center space-x-4">
          <span className="min-w-24">Distance: {distance.toFixed(2)}m</span>
          <Slider 
            value={[distance]}
            onValueChange={(value) => setDistance(value[0])}
            min={0}
            max={MAX_DISTANCE}
            step={0.1}
            className="w-full"
          />
        </div>
        
        <div className="relative w-full h-8 bg-gray-200 rounded-full overflow-hidden">
          <div className="flex h-full">
            {leds.map((color, index) => (
              <div
                key={index}
                className="flex-1 h-full transition-colors duration-200"
                style={{ backgroundColor: color }}
              />
            ))}
          </div>
        </div>

        <div className="space-y-2 text-sm">
          <div>Status Zones:</div>
          <div className="flex items-center space-x-2">
            <div className="w-4 h-4 bg-red-500"/> 
            <span>Too Close Zone (&lt; {minSafe}m)</span>
          </div>
          <div className="flex items-center space-x-2">
            <div className="w-4 h-4 bg-red-500"/>
            <span>Buffer Zone ({minSafe}m - {maxSafe}m)</span>
          </div>
          <div className="flex items-center space-x-2">
            <div className="w-4 h-4" style={{background: 'linear-gradient(to right, #ff0000, #00ff00)'}}/>
            <span>Approach Zone ({maxSafe}m - {MAX_DISTANCE}m)</span>
          </div>
          <div className="flex items-center space-x-2">
            <div className="w-4 h-4 bg-green-500"/>
            <span>Safe Zone (&gt; {MAX_DISTANCE}m)</span>
          </div>
        </div>
      </CardContent>
    </Card>
  );
};

export default GarageParkingAssistant;