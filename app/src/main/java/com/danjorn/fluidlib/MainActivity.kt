package com.danjorn.fluidlib

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import kotlinx.coroutines.MainScope
import kotlinx.coroutines.launch
import kotlin.concurrent.fixedRateTimer

class MainActivity : AppCompatActivity() {
    private var i = 0

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        setupSynth(this)
        changeInstrument(0, 40)

        fixedRateTimer(initialDelay = 1000, period = 1000, action = {
            MainScope().launch {
                playNext()
            }
        })
    }

    private fun playNext() {
        noteOff(0, 64 + i)
        noteOn(0, 64 + i)
    }
}