CF_EXTERN_C_BEGIN

#import <LightMessaging/sandbox.h>

enum SandboxContainerType
{
    AppContainer    = 1,
};

typedef struct
{
    const char* bundleId;
    const char* path;       // NULL to remove mapping

} SANDBOX_STATE_ITEM, *PSANDBOX_STATE_ITEM;

int sandbox_set_user_state_item(uid_t uid, int type, PSANDBOX_STATE_ITEM item, void* always_null);

CF_EXTERN_C_END

#define SANDBOX_OPERATION_default                           "default"
#define SANDBOX_OPERATION_appleevent_send                   "appleevent-send"
#define SANDBOX_OPERATION_authorization_right_obtain        "authorization-right-obtain"
#define SANDBOX_OPERATION_boot_arg_set                      "boot-arg-set"
#define SANDBOX_OPERATION_device_all                        "device*"
#define SANDBOX_OPERATION_device_camera                     "device-camera"
#define SANDBOX_OPERATION_device_microphone                 "device-microphone"
#define SANDBOX_OPERATION_distributed_notification_post     "distributed-notification-post"
#define SANDBOX_OPERATION_file_all                          "file*"
#define SANDBOX_OPERATION_file_chroot                       "file-chroot"
#define SANDBOX_OPERATION_file_ioctl                        "file-ioctl"
#define SANDBOX_OPERATION_file_issue_extension              "file-issue-extension"
#define SANDBOX_OPERATION_file_link                         "file-link"
#define SANDBOX_OPERATION_file_map_executable               "file-map-executable"
#define SANDBOX_OPERATION_file_mknod                        "file-mknod"
#define SANDBOX_OPERATION_file_mount                        "file-mount"
#define SANDBOX_OPERATION_file_mount_update                 "file-mount-update"
#define SANDBOX_OPERATION_file_read_all                     "file-read*"
#define SANDBOX_OPERATION_file_read_data                    "file-read-data"
#define SANDBOX_OPERATION_file_read_metadata                "file-read-metadata"
#define SANDBOX_OPERATION_file_read_xattr                   "file-read-xattr"
#define SANDBOX_OPERATION_file_revoke                       "file-revoke"
#define SANDBOX_OPERATION_file_search                       "file-search"
#define SANDBOX_OPERATION_file_unmount                      "file-unmount"
#define SANDBOX_OPERATION_file_write_all                    "file-write*"
#define SANDBOX_OPERATION_file_write_acl                    "file-write-acl"
#define SANDBOX_OPERATION_file_write_create                 "file-write-create"
#define SANDBOX_OPERATION_file_write_data                   "file-write-data"
#define SANDBOX_OPERATION_file_write_flags                  "file-write-flags"
#define SANDBOX_OPERATION_file_write_mode                   "file-write-mode"
#define SANDBOX_OPERATION_file_write_owner                  "file-write-owner"
#define SANDBOX_OPERATION_file_write_setugid                "file-write-setugid"
#define SANDBOX_OPERATION_file_write_times                  "file-write-times"
#define SANDBOX_OPERATION_file_write_unlink                 "file-write-unlink"
#define SANDBOX_OPERATION_file_write_xattr                  "file-write-xattr"
#define SANDBOX_OPERATION_fs_snapshot_all                   "fs-snapshot*"
#define SANDBOX_OPERATION_fs_snapshot_create                "fs-snapshot-create"
#define SANDBOX_OPERATION_fs_snapshot_delete                "fs-snapshot-delete"
#define SANDBOX_OPERATION_generic_issue_extension           "generic-issue-extension"
#define SANDBOX_OPERATION_qtn_user                          "qtn-user"
#define SANDBOX_OPERATION_hid_control                       "hid-control"
#define SANDBOX_OPERATION_iokit_all                         "iokit*"
#define SANDBOX_OPERATION_iokit_issue_extension             "iokit-issue-extension"
#define SANDBOX_OPERATION_iokit_open                        "iokit-open"
#define SANDBOX_OPERATION_iokit_set_properties              "iokit-set-properties"
#define SANDBOX_OPERATION_iokit_get_properties              "iokit-get-properties"
#define SANDBOX_OPERATION_ipc_all                           "ipc*"
#define SANDBOX_OPERATION_ipc_posix_all                     "ipc-posix*"
#define SANDBOX_OPERATION_ipc_posix_issue_extension         "ipc-posix-issue-extension"
#define SANDBOX_OPERATION_ipc_posix_sem                     "ipc-posix-sem"
#define SANDBOX_OPERATION_ipc_posix_shm_all                 "ipc-posix-shm*"
#define SANDBOX_OPERATION_ipc_posix_shm_read_all            "ipc-posix-shm-read*"
#define SANDBOX_OPERATION_ipc_posix_shm_read_data           "ipc-posix-shm-read-data"
#define SANDBOX_OPERATION_ipc_posix_shm_read_metadata       "ipc-posix-shm-read-metadata"
#define SANDBOX_OPERATION_ipc_posix_shm_write_all           "ipc-posix-shm-write*"
#define SANDBOX_OPERATION_ipc_posix_shm_write_create        "ipc-posix-shm-write-create"
#define SANDBOX_OPERATION_ipc_posix_shm_write_data          "ipc-posix-shm-write-data"
#define SANDBOX_OPERATION_ipc_posix_shm_write_unlink        "ipc-posix-shm-write-unlink"
#define SANDBOX_OPERATION_ipc_sysv_all                      "ipc-sysv*"
#define SANDBOX_OPERATION_ipc_sysv_msg                      "ipc-sysv-msg"
#define SANDBOX_OPERATION_ipc_sysv_sem                      "ipc-sysv-sem"
#define SANDBOX_OPERATION_ipc_sysv_shm                      "ipc-sysv-shm"
#define SANDBOX_OPERATION_job_creation                      "job-creation"
#define SANDBOX_OPERATION_load_unsigned_code                "load-unsigned-code"
#define SANDBOX_OPERATION_lsopen                            "lsopen"
#define SANDBOX_OPERATION_mach_all                          "mach*"
#define SANDBOX_OPERATION_mach_cross_domain_lookup          "mach-cross-domain-lookup"
#define SANDBOX_OPERATION_mach_host_all                     "mach-host*"
#define SANDBOX_OPERATION_mach_host_exception_port_set      "mach-host-exception-port-set"
#define SANDBOX_OPERATION_mach_host_special_port_set        "mach-host-special-port-set"
#define SANDBOX_OPERATION_mach_issue_extension              "mach-issue-extension"
#define SANDBOX_OPERATION_mach_lookup                       "mach-lookup"
#define SANDBOX_OPERATION_mach_per_user_lookup              "mach-per-user-lookup"
#define SANDBOX_OPERATION_mach_priv_all                     "mach-priv*"
#define SANDBOX_OPERATION_mach_priv_host_port               "mach-priv-host-port"
#define SANDBOX_OPERATION_mach_priv_task_port               "mach-priv-task-port"
#define SANDBOX_OPERATION_mach_register                     "mach-register"
#define SANDBOX_OPERATION_mach_task_name                    "mach-task-name"
#define SANDBOX_OPERATION_network_all                       "network*"
#define SANDBOX_OPERATION_network_inbound                   "network-inbound"
#define SANDBOX_OPERATION_network_bind                      "network-bind"
#define SANDBOX_OPERATION_network_outbound                  "network-outbound"
#define SANDBOX_OPERATION_nvram_all                         "nvram*"
#define SANDBOX_OPERATION_nvram_delete                      "nvram-delete"
#define SANDBOX_OPERATION_nvram_get                         "nvram-get"
#define SANDBOX_OPERATION_nvram_set                         "nvram-set"
#define SANDBOX_OPERATION_user_preference_all               "user-preference*"
#define SANDBOX_OPERATION_user_preference_read              "user-preference-read"
#define SANDBOX_OPERATION_user_preference_write             "user-preference-write"
#define SANDBOX_OPERATION_process_all                       "process*"
#define SANDBOX_OPERATION_process_codesigning_status_all    "process-codesigning-status*"
#define SANDBOX_OPERATION_process_codesigning_status_set    "process-codesigning-status-set"
#define SANDBOX_OPERATION_process_codesigning_status_get    "process-codesigning-status-get"
#define SANDBOX_OPERATION_process_exec_all                  "process-exec*"
#define SANDBOX_OPERATION_process_exec_interpreter          "process-exec-interpreter"
#define SANDBOX_OPERATION_process_fork                      "process-fork"
#define SANDBOX_OPERATION_process_info_all                  "process-info*"
#define SANDBOX_OPERATION_process_info_codesignature        "process-info-codesignature"
#define SANDBOX_OPERATION_process_info_dirtycontrol         "process-info-dirtycontrol"
#define SANDBOX_OPERATION_process_info_listpids             "process-info-listpids"
#define SANDBOX_OPERATION_process_info_rusage               "process-info-rusage"
#define SANDBOX_OPERATION_process_info_pidinfo              "process-info-pidinfo"
#define SANDBOX_OPERATION_process_info_pidfdinfo            "process-info-pidfdinfo"
#define SANDBOX_OPERATION_process_info_pidfileportinfo      "process-info-pidfileportinfo"
#define SANDBOX_OPERATION_process_info_setcontrol           "process-info-setcontrol"
#define SANDBOX_OPERATION_pseudo_tty                        "pseudo-tty"
#define SANDBOX_OPERATION_signal                            "signal"
#define SANDBOX_OPERATION_sysctl_all                        "sysctl*"
#define SANDBOX_OPERATION_sysctl_read                       "sysctl-read"
#define SANDBOX_OPERATION_sysctl_write                      "sysctl-write"
#define SANDBOX_OPERATION_system_all                        "system*"
#define SANDBOX_OPERATION_system_acct                       "system-acct"
#define SANDBOX_OPERATION_system_audit                      "system-audit"
#define SANDBOX_OPERATION_system_chud                       "system-chud"
#define SANDBOX_OPERATION_system_debug                      "system-debug"
#define SANDBOX_OPERATION_system_fsctl                      "system-fsctl"
#define SANDBOX_OPERATION_system_info                       "system-info"
#define SANDBOX_OPERATION_system_kext_all                   "system-kext*"
#define SANDBOX_OPERATION_system_kext_load                  "system-kext-load"
#define SANDBOX_OPERATION_system_kext_unload                "system-kext-unload"
#define SANDBOX_OPERATION_system_kext_query                 "system-kext-query"
#define SANDBOX_OPERATION_system_mac_label                  "system-mac-label"
#define SANDBOX_OPERATION_system_nfssvc                     "system-nfssvc"
#define SANDBOX_OPERATION_system_package_check              "system-package-check"
#define SANDBOX_OPERATION_system_privilege                  "system-privilege"
#define SANDBOX_OPERATION_system_reboot                     "system-reboot"
#define SANDBOX_OPERATION_system_sched                      "system-sched"
#define SANDBOX_OPERATION_system_set_time                   "system-set-time"
#define SANDBOX_OPERATION_system_socket                     "system-socket"
#define SANDBOX_OPERATION_system_suspend_resume             "system-suspend-resume"
#define SANDBOX_OPERATION_system_swap                       "system-swap"