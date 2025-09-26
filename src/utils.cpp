/**
 * Stellar Data Recovery Pro Free - Utility Functions Implementation
 * 
 * This file contains utility functions for the Stellar Data Recovery application.
 * 
 * @author Stellar Information Technology
 * @version 1.0.0
 * @date 2024-09-27
 */

#include \"stellar_recovery.h\"
#include <sstream>
#include <iomanip>
#include <random>
#include <filesystem>
#include <ctime>

namespace Stellar {
    namespace Recovery {
        namespace Utils {
            
            /**
             * Format file size in human-readable format
             */
            std::string FormatFileSize(uint64_t bytes) {
                const char* units[] = {\"B\", \"KB\", \"MB\", \"GB\", \"TB\", \"PB\"};
                int unit = 0;
                double size = static_cast<double>(bytes);
                
                while (size >= 1024.0 && unit < 5) {
                    size /= 1024.0;
                    unit++;
                }
                
                std::ostringstream oss;
                if (unit == 0) {
                    oss << static_cast<uint64_t>(size) << \" \" << units[unit];
                } else {
                    oss << std::fixed << std::setprecision(2) << size << \" \" << units[unit];
                }
                return oss.str();
            }
            
            /**
             * Format duration in human-readable format
             */
            std::string FormatDuration(const std::chrono::duration<double>& duration) {
                auto seconds = duration.count();
                
                if (seconds < 60) {
                    return std::to_string(static_cast<int>(seconds)) + \" seconds\";
                } else if (seconds < 3600) {
                    int minutes = static_cast<int>(seconds / 60);
                    int remainingSeconds = static_cast<int>(seconds) % 60;
                    return std::to_string(minutes) + \"m \" + std::to_string(remainingSeconds) + \"s\";
                } else {
                    int hours = static_cast<int>(seconds / 3600);
                    int minutes = static_cast<int>((seconds - hours * 3600) / 60);
                    return std::to_string(hours) + \"h \" + std::to_string(minutes) + \"m\";
                }
            }
            
            /**
             * Get file type string representation
             */
            std::string GetFileTypeString(TargetFileType type) {
                switch (type) {
                    case TargetFileType::PHOTO: return \"Photos\";
                    case TargetFileType::VIDEO: return \"Videos\";
                    case TargetFileType::AUDIO: return \"Audio Files\";
                    case TargetFileType::DOCUMENT: return \"Documents\";
                    case TargetFileType::EMAIL: return \"Email Files\";
                    case TargetFileType::ARCHIVE: return \"Archives\";
                    case TargetFileType::EXECUTABLE: return \"Executables\";
                    case TargetFileType::DATABASE: return \"Databases\";
                    case TargetFileType::ALL_DATA: return \"All Data\";
                    default: return \"Unknown\";
                }
            }
            
            /**
             * Get scan mode string representation
             */
            std::string GetScanModeString(ScanMode mode) {
                switch (mode) {
                    case ScanMode::QUICK_SCAN: return \"Quick Scan\";
                    case ScanMode::DEEP_SCAN: return \"Deep Scan\";
                    case ScanMode::RAW_RECOVERY: return \"Raw Recovery\";
                    case ScanMode::PARTITION_RECOVERY: return \"Partition Recovery\";
                    case ScanMode::CUSTOM_SCAN: return \"Custom Scan\";
                    default: return \"Unknown Mode\";
                }
            }
            
            /**
             * Get device type string representation
             */
            std::string GetDeviceTypeString(DeviceType type) {
                switch (type) {
                    case DeviceType::HDD: return \"Hard Disk Drive\";
                    case DeviceType::SSD: return \"Solid State Drive\";
                    case DeviceType::USB: return \"USB Drive\";
                    case DeviceType::SD_CARD: return \"SD Card\";
                    case DeviceType::CF_CARD: return \"CompactFlash Card\";
                    case DeviceType::CD_DVD: return \"CD/DVD\";
                    case DeviceType::RAID: return \"RAID Array\";
                    case DeviceType::NETWORK: return \"Network Drive\";
                    case DeviceType::VIRTUAL: return \"Virtual Drive\";
                    case DeviceType::UNKNOWN: return \"Unknown Device\";
                    default: return \"Unspecified\";
                }
            }
            
            /**
             * Get file system string representation
             */
            std::string GetFileSystemString(FileSystemType fs) {
                switch (fs) {
                    case FileSystemType::NTFS: return \"NTFS\";
                    case FileSystemType::FAT16: return \"FAT16\";
                    case FileSystemType::FAT32: return \"FAT32\";
                    case FileSystemType::EXFAT: return \"exFAT\";
                    case FileSystemType::REFS: return \"ReFS\";
                    case FileSystemType::APFS: return \"APFS\";
                    case FileSystemType::HFS_PLUS: return \"HFS+\";
                    case FileSystemType::EXT2: return \"ext2\";
                    case FileSystemType::EXT3: return \"ext3\";
                    case FileSystemType::EXT4: return \"ext4\";
                    case FileSystemType::XFS: return \"XFS\";
                    case FileSystemType::BTRFS: return \"Btrfs\";
                    case FileSystemType::UDF: return \"UDF\";
                    case FileSystemType::ISO9660: return \"ISO 9660\";
                    case FileSystemType::UNKNOWN: return \"Unknown\";
                    default: return \"Unspecified\";
                }
            }
            
            /**
             * Validate recovery path
             */
            bool IsValidRecoveryPath(const std::string& path) {
                if (path.empty()) {
                    return false;
                }
                
                try {
                    std::filesystem::path fsPath(path);
                    
                    // Check if parent directory exists
                    if (fsPath.has_parent_path()) {
                        return std::filesystem::exists(fsPath.parent_path());
                    }
                    
                    return true;
                } catch (const std::exception&) {
                    return false;
                }
            }
            
            /**
             * Generate unique session ID
             */
            std::string GenerateSessionId() {
                auto now = std::chrono::system_clock::now();
                auto time_t = std::chrono::system_clock::to_time_t(now);
                auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                    now.time_since_epoch()) % 1000;
                
                std::ostringstream oss;
                oss << \"STELLAR_\" << std::put_time(std::localtime(&time_t), \"%Y%m%d_%H%M%S\") 
                    << \"_\" << std::setfill('0') << std::setw(3) << ms.count();
                
                return oss.str();
            }
            
        } // namespace Utils
    } // namespace Recovery
} // namespace Stellar