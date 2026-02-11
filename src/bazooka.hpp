#pragma once
#include "miniaudio.h"
#include "worker.hpp"

#include <string>
#include <chrono>

namespace ch = std::chrono;
namespace fs = std::filesystem;

//-----------------------------------------------------------------------------|
//-- CBazooka -----------------------------------------------------------------|
//-----------------------------------------------------------------------------|

class CBazooka
{
public:
    CBazooka(const void* resource, std::size_t size);
    ~CBazooka();

    void Play();
    void Text(const std::string& str);
    void Sleep(uint32_t time);

    constexpr static ch::milliseconds k_PrintDelay{50};
    constexpr static uint32_t k_NumChannels = 2;
    constexpr static uint32_t k_SampleRate = 44100;
    constexpr static ma_format k_AudioFormat = ma_format_s16;

private:
    void InitMA();
    void ShutdownMA();
    void LoadMusicResource(const void* resource, std::size_t size);

    CWorkerThread m_PrintThread;

    ma_engine m_AudioEngine;
    ma_sound m_Track;
    ma_decoder m_Decoder;
    ma_decoder_config m_DecoderConfig;
};