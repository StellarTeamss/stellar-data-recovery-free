#pragma once
/**
 * Stellar Data Recovery Pro Free - Core Header File
 * 
 * This header contains the core definitions and classes for the
 * Stellar Data Recovery application.
 * 
 * @author Stellar Information Technology
 * @version 1.0.0
 * @date 2024-09-27
 */

#ifndef STELLAR_RECOVERY_H
#define STELLAR_RECOVERY_H

#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <functional>
#include <windows.h>

namespace Stellar {
    namespace Recovery {
        
        // Version information
        constexpr const char* VERSION = \"1.0.0\";
        constexpr const char* BUILD_DATE = __DATE__;
        constexpr const char* BUILD_TIME = __TIME__;
        
        // Recovery modes
        enum class ScanMode {
            QUICK_SCAN,          // Fast scan for recently deleted files
            DEEP_SCAN,           // Thorough scan for all recoverable data
            RAW_RECOVERY,        // Sector-by-sector scan
            PARTITION_RECOVERY,  // Recover lost partitions
            CUSTOM_SCAN          // User-defined scan parameters
        };
        
        // File types for targeted recovery
        enum class TargetFileType {
            PHOTO,      // Images: JPG, PNG, GIF, BMP, TIFF, RAW
            VIDEO,      // Videos: MP4, AVI, MOV, WMV, FLV, 3GP
            AUDIO,      // Audio: MP3, WAV, FLAC, AAC, OGG
            DOCUMENT,   // Documents: DOC, DOCX, PDF, XLS, XLSX, PPT
            EMAIL,      // Emails: PST, EML, MSG, MBOX
            ARCHIVE,    // Archives: ZIP, RAR, 7Z, TAR, GZ
            EXECUTABLE, // Executables: EXE, DLL, MSI
            DATABASE,   // Databases: DB, MDB, ACCDB, SQL
            ALL_DATA    // All file types
        };
        
        // Storage device types
        enum class DeviceType {
            HDD,        // Hard Disk Drive
            SSD,        // Solid State Drive
            USB,        // USB Flash Drive
            SD_CARD,    // SD/microSD Card
            CF_CARD,    // CompactFlash Card
            CD_DVD,     // Optical Disc
            RAID,       // RAID Array
            NETWORK,    // Network Drive
            VIRTUAL,    // Virtual Drive
            UNKNOWN     // Unknown device type
        };
        
        // File system types
        enum class FileSystemType {
            NTFS,
            FAT16,
            FAT32,
            EXFAT,
            REFS,
            APFS,
            HFS_PLUS,
            EXT2,
            EXT3,
            EXT4,
            XFS,
            BTRFS,
            UDF,
            ISO9660,
            UNKNOWN
        };
        
        // Recovery result status
        enum class RecoveryStatus {
            PENDING,
            IN_PROGRESS,
            COMPLETED,
            FAILED,
            PARTIALLY_RECOVERED,
            SKIPPED
        };
        
        // Drive information structure
        struct DriveInformation {
            std::string driveLetter;
            std::string volumeLabel;
            std::string serialNumber;
            FileSystemType fileSystem;
            DeviceType deviceType;
            uint64_t totalCapacity;
            uint64_t freeSpace;
            uint64_t usedSpace;
            bool isAccessible;
            bool isRemovable;
            bool isSystemDrive;
            std::string manufacturer;
            std::string model;
            
            DriveInformation() :
                fileSystem(FileSystemType::UNKNOWN),
                deviceType(DeviceType::UNKNOWN),
                totalCapacity(0),
                freeSpace(0),
                usedSpace(0),
                isAccessible(false),
                isRemovable(false),
                isSystemDrive(false) {}
        };
        
        // Recoverable file information
        struct RecoverableFile {
            std::string fileName;
            std::string originalPath;
            std::string recoveryPath;
            TargetFileType fileType;
            uint64_t fileSize;
            std::chrono::system_clock::time_point dateCreated;
            std::chrono::system_clock::time_point dateModified;
            std::chrono::system_clock::time_point dateAccessed;
            double recoveryConfidence;  // 0.0 to 1.0
            RecoveryStatus status;
            bool isEncrypted;
            bool isCompressed;
            bool hasPreview;
            std::string checksum;
            
            RecoverableFile() :
                fileType(TargetFileType::ALL_DATA),
                fileSize(0),
                recoveryConfidence(0.0),
                status(RecoveryStatus::PENDING),
                isEncrypted(false),
                isCompressed(false),
                hasPreview(false) {}
        };
        
        // Recovery session information
        struct RecoverySession {
            std::string sessionId;
            std::string sourceDrive;
            std::string targetPath;
            ScanMode scanMode;
            TargetFileType targetType;
            std::chrono::system_clock::time_point startTime;
            std::chrono::system_clock::time_point endTime;
            uint32_t totalFilesFound;
            uint32_t filesRecovered;
            uint64_t totalDataRecovered;
            bool isComplete;
            std::string lastError;
            
            RecoverySession() :
                scanMode(ScanMode::QUICK_SCAN),
                targetType(TargetFileType::ALL_DATA),
                totalFilesFound(0),
                filesRecovered(0),
                totalDataRecovered(0),
                isComplete(false) {}
        };
        
        // Progress callback function type
        using ProgressCallback = std::function<void(int percentage, const std::string& operation)>;
        
        // Utility functions
        namespace Utils {
            std::string FormatFileSize(uint64_t bytes);
            std::string FormatDuration(const std::chrono::duration<double>& duration);
            std::string GetFileTypeString(TargetFileType type);
            std::string GetScanModeString(ScanMode mode);
            std::string GetDeviceTypeString(DeviceType type);
            std::string GetFileSystemString(FileSystemType fs);
            bool IsValidRecoveryPath(const std::string& path);
            std::string GenerateSessionId();
        }
        
        // Forward declarations
        class RecoveryEngine;
        class DriveAnalyzer;
        class FileSystemScanner;
        class DataExtractor;
        class PreviewGenerator;
        class RecoveryLogger;
        
    } // namespace Recovery
} // namespace Stellar

#endif // STELLAR_RECOVERY_H