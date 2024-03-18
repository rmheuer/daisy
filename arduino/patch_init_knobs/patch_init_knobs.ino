/*

    mplsartindustry/daisy
    Copyright (c) 2024 held jointly by the individual authors.

    This file is part of mplsartindustry/daisy.

    mplsartindustry/daisy is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    mplsartindustry/daisy is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with mplsartindustry/daisy.  If not, see <http://www.gnu.org/licenses/>.

*/
#include "DaisyDuino.h"

DaisyHardware patch;

void setup() {
  // initialize hardware
  patch = DAISY.init(DAISY_PATCH_SM);
}

void loop() {

  // update inputs
  patch.ProcessAllControls();

  // cv_1, CV_1 pot
  float cv_1 = patch.AnalogReadToVolts(analogRead(PIN_PATCH_SM_CV_1));

  // cv_2, CV_2 pot
  float cv_2 = patch.AnalogReadToVolts(analogRead(PIN_PATCH_SM_CV_2));

  // cv_3, CV_3 pot
  float cv_3 = patch.AnalogReadToVolts(analogRead(PIN_PATCH_SM_CV_3));

  // cv_4, CV_4 pot
  float cv_4 = patch.AnalogReadToVolts(analogRead(PIN_PATCH_SM_CV_4));

  // cv_out_1, C10 output jack
  float cv_out_1 = cv_1 + (cv_2 * 0.5f) + (cv_3 * 0.25f) + (cv_4 * 0.125f);
  cv_out_1 = min(5.0f, max(-5.0f, cv_out_1));
  patch.WriteCvOut(PIN_PATCH_SM_CV_OUT_1, cv_out_1);

  // cv_out_2, C1 led on front panel
  float cv_out_2 = max(0.0f, cv_out_1);
  patch.WriteCvOut(PIN_PATCH_SM_CV_OUT_2, cv_out_2);

}

