#include "bazooka.hpp"
#include "worker.hpp"

#include <iostream>

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

//-----------------------------------------------------------------------------|
//-- CBazooka -----------------------------------------------------------------|
//-----------------------------------------------------------------------------|

CBazooka::CBazooka(const void* resource, std::size_t size)
{
    ma_engine_init(nullptr, &m_AudioEngine);
    m_DecoderConfig = ma_decoder_config_init(k_AudioFormat, k_NumChannels, k_SampleRate);
    LoadMusicResource(resource, size);
}

CBazooka::~CBazooka()
{
    ma_sound_uninit(&m_Track);
    ma_engine_uninit(&m_AudioEngine);
    ma_decoder_uninit(&m_Decoder);
}

void CBazooka::LoadMusicResource(const void* resource, std::size_t size)
{
    ma_decoder_init_memory(resource, size, &m_DecoderConfig, &m_Decoder);
    ma_data_source* src = &m_Decoder;
    ma_sound_init_from_data_source(&m_AudioEngine, src, 0, nullptr, &m_Track);
}

void CBazooka::Play()
{
    ma_sound_start(&m_Track);

    float length;
    ma_sound_get_length_in_seconds(&m_Track, &length);

    std::this_thread::sleep_for(ch::seconds(static_cast<int>(length + 1)));
}

void CBazooka::Text(const std::string& str)
{
    m_PrintThread.AddCommand([str]{   
            for (char c : str)
            {
                std::cout << c << std::flush;
                std::this_thread::sleep_for(k_PrintDelay);
            }
            std::cout << "\n";
        });

}

void CBazooka::Sleep(uint32_t time)
{
    m_PrintThread.AddCommand([time]{ std::this_thread::sleep_for(ch::milliseconds(time)); });
}