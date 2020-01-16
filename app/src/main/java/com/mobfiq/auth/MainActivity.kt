package com.mobfiq.auth

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_main.*
import kotlinx.coroutines.runBlocking

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val handler = AuthHandler("https://api-homolog-cobasiv2.mobfiq.com.br/api/getaccesstoken", "cobasi", "cbe365e53f20f5d658256f6147e714c7d5914692b8a7113a7730fc49f6252949")

        runBlocking {
            handler.requestAccessToken()
        }

        sample_text.text = "Access Token: ${handler.accessToken}.\nExpires in: ${handler.expirationTime}"

        //Esta Branch tem a finalidade de importar os arquivos .cpp e .h de uma biblioteca remota.
    }
}