################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThreadX/common/src/tx_block_allocate.c \
../ThreadX/common/src/tx_block_pool_cleanup.c \
../ThreadX/common/src/tx_block_pool_create.c \
../ThreadX/common/src/tx_block_pool_delete.c \
../ThreadX/common/src/tx_block_pool_info_get.c \
../ThreadX/common/src/tx_block_pool_initialize.c \
../ThreadX/common/src/tx_block_pool_performance_info_get.c \
../ThreadX/common/src/tx_block_pool_performance_system_info_get.c \
../ThreadX/common/src/tx_block_pool_prioritize.c \
../ThreadX/common/src/tx_block_release.c \
../ThreadX/common/src/tx_byte_allocate.c \
../ThreadX/common/src/tx_byte_pool_cleanup.c \
../ThreadX/common/src/tx_byte_pool_create.c \
../ThreadX/common/src/tx_byte_pool_delete.c \
../ThreadX/common/src/tx_byte_pool_info_get.c \
../ThreadX/common/src/tx_byte_pool_initialize.c \
../ThreadX/common/src/tx_byte_pool_performance_info_get.c \
../ThreadX/common/src/tx_byte_pool_performance_system_info_get.c \
../ThreadX/common/src/tx_byte_pool_prioritize.c \
../ThreadX/common/src/tx_byte_pool_search.c \
../ThreadX/common/src/tx_byte_release.c \
../ThreadX/common/src/tx_event_flags_cleanup.c \
../ThreadX/common/src/tx_event_flags_create.c \
../ThreadX/common/src/tx_event_flags_delete.c \
../ThreadX/common/src/tx_event_flags_get.c \
../ThreadX/common/src/tx_event_flags_info_get.c \
../ThreadX/common/src/tx_event_flags_initialize.c \
../ThreadX/common/src/tx_event_flags_performance_info_get.c \
../ThreadX/common/src/tx_event_flags_performance_system_info_get.c \
../ThreadX/common/src/tx_event_flags_set.c \
../ThreadX/common/src/tx_event_flags_set_notify.c \
../ThreadX/common/src/tx_initialize_high_level.c \
../ThreadX/common/src/tx_initialize_kernel_enter.c \
../ThreadX/common/src/tx_initialize_kernel_setup.c \
../ThreadX/common/src/tx_misra.c \
../ThreadX/common/src/tx_mutex_cleanup.c \
../ThreadX/common/src/tx_mutex_create.c \
../ThreadX/common/src/tx_mutex_delete.c \
../ThreadX/common/src/tx_mutex_get.c \
../ThreadX/common/src/tx_mutex_info_get.c \
../ThreadX/common/src/tx_mutex_initialize.c \
../ThreadX/common/src/tx_mutex_performance_info_get.c \
../ThreadX/common/src/tx_mutex_performance_system_info_get.c \
../ThreadX/common/src/tx_mutex_prioritize.c \
../ThreadX/common/src/tx_mutex_priority_change.c \
../ThreadX/common/src/tx_mutex_put.c \
../ThreadX/common/src/tx_queue_cleanup.c \
../ThreadX/common/src/tx_queue_create.c \
../ThreadX/common/src/tx_queue_delete.c \
../ThreadX/common/src/tx_queue_flush.c \
../ThreadX/common/src/tx_queue_front_send.c \
../ThreadX/common/src/tx_queue_info_get.c \
../ThreadX/common/src/tx_queue_initialize.c \
../ThreadX/common/src/tx_queue_performance_info_get.c \
../ThreadX/common/src/tx_queue_performance_system_info_get.c \
../ThreadX/common/src/tx_queue_prioritize.c \
../ThreadX/common/src/tx_queue_receive.c \
../ThreadX/common/src/tx_queue_send.c \
../ThreadX/common/src/tx_queue_send_notify.c \
../ThreadX/common/src/tx_semaphore_ceiling_put.c \
../ThreadX/common/src/tx_semaphore_cleanup.c \
../ThreadX/common/src/tx_semaphore_create.c \
../ThreadX/common/src/tx_semaphore_delete.c \
../ThreadX/common/src/tx_semaphore_get.c \
../ThreadX/common/src/tx_semaphore_info_get.c \
../ThreadX/common/src/tx_semaphore_initialize.c \
../ThreadX/common/src/tx_semaphore_performance_info_get.c \
../ThreadX/common/src/tx_semaphore_performance_system_info_get.c \
../ThreadX/common/src/tx_semaphore_prioritize.c \
../ThreadX/common/src/tx_semaphore_put.c \
../ThreadX/common/src/tx_semaphore_put_notify.c \
../ThreadX/common/src/tx_thread_create.c \
../ThreadX/common/src/tx_thread_delete.c \
../ThreadX/common/src/tx_thread_entry_exit_notify.c \
../ThreadX/common/src/tx_thread_identify.c \
../ThreadX/common/src/tx_thread_info_get.c \
../ThreadX/common/src/tx_thread_initialize.c \
../ThreadX/common/src/tx_thread_performance_info_get.c \
../ThreadX/common/src/tx_thread_performance_system_info_get.c \
../ThreadX/common/src/tx_thread_preemption_change.c \
../ThreadX/common/src/tx_thread_priority_change.c \
../ThreadX/common/src/tx_thread_relinquish.c \
../ThreadX/common/src/tx_thread_reset.c \
../ThreadX/common/src/tx_thread_resume.c \
../ThreadX/common/src/tx_thread_shell_entry.c \
../ThreadX/common/src/tx_thread_sleep.c \
../ThreadX/common/src/tx_thread_stack_analyze.c \
../ThreadX/common/src/tx_thread_stack_error_handler.c \
../ThreadX/common/src/tx_thread_stack_error_notify.c \
../ThreadX/common/src/tx_thread_suspend.c \
../ThreadX/common/src/tx_thread_system_preempt_check.c \
../ThreadX/common/src/tx_thread_system_resume.c \
../ThreadX/common/src/tx_thread_system_suspend.c \
../ThreadX/common/src/tx_thread_terminate.c \
../ThreadX/common/src/tx_thread_time_slice.c \
../ThreadX/common/src/tx_thread_time_slice_change.c \
../ThreadX/common/src/tx_thread_timeout.c \
../ThreadX/common/src/tx_thread_wait_abort.c \
../ThreadX/common/src/tx_time_get.c \
../ThreadX/common/src/tx_time_set.c \
../ThreadX/common/src/tx_timer_activate.c \
../ThreadX/common/src/tx_timer_change.c \
../ThreadX/common/src/tx_timer_create.c \
../ThreadX/common/src/tx_timer_deactivate.c \
../ThreadX/common/src/tx_timer_delete.c \
../ThreadX/common/src/tx_timer_expiration_process.c \
../ThreadX/common/src/tx_timer_info_get.c \
../ThreadX/common/src/tx_timer_initialize.c \
../ThreadX/common/src/tx_timer_performance_info_get.c \
../ThreadX/common/src/tx_timer_performance_system_info_get.c \
../ThreadX/common/src/tx_timer_system_activate.c \
../ThreadX/common/src/tx_timer_system_deactivate.c \
../ThreadX/common/src/tx_timer_thread_entry.c \
../ThreadX/common/src/tx_trace_buffer_full_notify.c \
../ThreadX/common/src/tx_trace_disable.c \
../ThreadX/common/src/tx_trace_enable.c \
../ThreadX/common/src/tx_trace_event_filter.c \
../ThreadX/common/src/tx_trace_event_unfilter.c \
../ThreadX/common/src/tx_trace_initialize.c \
../ThreadX/common/src/tx_trace_interrupt_control.c \
../ThreadX/common/src/tx_trace_isr_enter_insert.c \
../ThreadX/common/src/tx_trace_isr_exit_insert.c \
../ThreadX/common/src/tx_trace_object_register.c \
../ThreadX/common/src/tx_trace_object_unregister.c \
../ThreadX/common/src/tx_trace_user_event_insert.c \
../ThreadX/common/src/txe_block_allocate.c \
../ThreadX/common/src/txe_block_pool_create.c \
../ThreadX/common/src/txe_block_pool_delete.c \
../ThreadX/common/src/txe_block_pool_info_get.c \
../ThreadX/common/src/txe_block_pool_prioritize.c \
../ThreadX/common/src/txe_block_release.c \
../ThreadX/common/src/txe_byte_allocate.c \
../ThreadX/common/src/txe_byte_pool_create.c \
../ThreadX/common/src/txe_byte_pool_delete.c \
../ThreadX/common/src/txe_byte_pool_info_get.c \
../ThreadX/common/src/txe_byte_pool_prioritize.c \
../ThreadX/common/src/txe_byte_release.c \
../ThreadX/common/src/txe_event_flags_create.c \
../ThreadX/common/src/txe_event_flags_delete.c \
../ThreadX/common/src/txe_event_flags_get.c \
../ThreadX/common/src/txe_event_flags_info_get.c \
../ThreadX/common/src/txe_event_flags_set.c \
../ThreadX/common/src/txe_event_flags_set_notify.c \
../ThreadX/common/src/txe_mutex_create.c \
../ThreadX/common/src/txe_mutex_delete.c \
../ThreadX/common/src/txe_mutex_get.c \
../ThreadX/common/src/txe_mutex_info_get.c \
../ThreadX/common/src/txe_mutex_prioritize.c \
../ThreadX/common/src/txe_mutex_put.c \
../ThreadX/common/src/txe_queue_create.c \
../ThreadX/common/src/txe_queue_delete.c \
../ThreadX/common/src/txe_queue_flush.c \
../ThreadX/common/src/txe_queue_front_send.c \
../ThreadX/common/src/txe_queue_info_get.c \
../ThreadX/common/src/txe_queue_prioritize.c \
../ThreadX/common/src/txe_queue_receive.c \
../ThreadX/common/src/txe_queue_send.c \
../ThreadX/common/src/txe_queue_send_notify.c \
../ThreadX/common/src/txe_semaphore_ceiling_put.c \
../ThreadX/common/src/txe_semaphore_create.c \
../ThreadX/common/src/txe_semaphore_delete.c \
../ThreadX/common/src/txe_semaphore_get.c \
../ThreadX/common/src/txe_semaphore_info_get.c \
../ThreadX/common/src/txe_semaphore_prioritize.c \
../ThreadX/common/src/txe_semaphore_put.c \
../ThreadX/common/src/txe_semaphore_put_notify.c \
../ThreadX/common/src/txe_thread_create.c \
../ThreadX/common/src/txe_thread_delete.c \
../ThreadX/common/src/txe_thread_entry_exit_notify.c \
../ThreadX/common/src/txe_thread_info_get.c \
../ThreadX/common/src/txe_thread_preemption_change.c \
../ThreadX/common/src/txe_thread_priority_change.c \
../ThreadX/common/src/txe_thread_relinquish.c \
../ThreadX/common/src/txe_thread_reset.c \
../ThreadX/common/src/txe_thread_resume.c \
../ThreadX/common/src/txe_thread_suspend.c \
../ThreadX/common/src/txe_thread_terminate.c \
../ThreadX/common/src/txe_thread_time_slice_change.c \
../ThreadX/common/src/txe_thread_wait_abort.c \
../ThreadX/common/src/txe_timer_activate.c \
../ThreadX/common/src/txe_timer_change.c \
../ThreadX/common/src/txe_timer_create.c \
../ThreadX/common/src/txe_timer_deactivate.c \
../ThreadX/common/src/txe_timer_delete.c \
../ThreadX/common/src/txe_timer_info_get.c 

OBJS += \
./ThreadX/common/src/tx_block_allocate.o \
./ThreadX/common/src/tx_block_pool_cleanup.o \
./ThreadX/common/src/tx_block_pool_create.o \
./ThreadX/common/src/tx_block_pool_delete.o \
./ThreadX/common/src/tx_block_pool_info_get.o \
./ThreadX/common/src/tx_block_pool_initialize.o \
./ThreadX/common/src/tx_block_pool_performance_info_get.o \
./ThreadX/common/src/tx_block_pool_performance_system_info_get.o \
./ThreadX/common/src/tx_block_pool_prioritize.o \
./ThreadX/common/src/tx_block_release.o \
./ThreadX/common/src/tx_byte_allocate.o \
./ThreadX/common/src/tx_byte_pool_cleanup.o \
./ThreadX/common/src/tx_byte_pool_create.o \
./ThreadX/common/src/tx_byte_pool_delete.o \
./ThreadX/common/src/tx_byte_pool_info_get.o \
./ThreadX/common/src/tx_byte_pool_initialize.o \
./ThreadX/common/src/tx_byte_pool_performance_info_get.o \
./ThreadX/common/src/tx_byte_pool_performance_system_info_get.o \
./ThreadX/common/src/tx_byte_pool_prioritize.o \
./ThreadX/common/src/tx_byte_pool_search.o \
./ThreadX/common/src/tx_byte_release.o \
./ThreadX/common/src/tx_event_flags_cleanup.o \
./ThreadX/common/src/tx_event_flags_create.o \
./ThreadX/common/src/tx_event_flags_delete.o \
./ThreadX/common/src/tx_event_flags_get.o \
./ThreadX/common/src/tx_event_flags_info_get.o \
./ThreadX/common/src/tx_event_flags_initialize.o \
./ThreadX/common/src/tx_event_flags_performance_info_get.o \
./ThreadX/common/src/tx_event_flags_performance_system_info_get.o \
./ThreadX/common/src/tx_event_flags_set.o \
./ThreadX/common/src/tx_event_flags_set_notify.o \
./ThreadX/common/src/tx_initialize_high_level.o \
./ThreadX/common/src/tx_initialize_kernel_enter.o \
./ThreadX/common/src/tx_initialize_kernel_setup.o \
./ThreadX/common/src/tx_misra.o \
./ThreadX/common/src/tx_mutex_cleanup.o \
./ThreadX/common/src/tx_mutex_create.o \
./ThreadX/common/src/tx_mutex_delete.o \
./ThreadX/common/src/tx_mutex_get.o \
./ThreadX/common/src/tx_mutex_info_get.o \
./ThreadX/common/src/tx_mutex_initialize.o \
./ThreadX/common/src/tx_mutex_performance_info_get.o \
./ThreadX/common/src/tx_mutex_performance_system_info_get.o \
./ThreadX/common/src/tx_mutex_prioritize.o \
./ThreadX/common/src/tx_mutex_priority_change.o \
./ThreadX/common/src/tx_mutex_put.o \
./ThreadX/common/src/tx_queue_cleanup.o \
./ThreadX/common/src/tx_queue_create.o \
./ThreadX/common/src/tx_queue_delete.o \
./ThreadX/common/src/tx_queue_flush.o \
./ThreadX/common/src/tx_queue_front_send.o \
./ThreadX/common/src/tx_queue_info_get.o \
./ThreadX/common/src/tx_queue_initialize.o \
./ThreadX/common/src/tx_queue_performance_info_get.o \
./ThreadX/common/src/tx_queue_performance_system_info_get.o \
./ThreadX/common/src/tx_queue_prioritize.o \
./ThreadX/common/src/tx_queue_receive.o \
./ThreadX/common/src/tx_queue_send.o \
./ThreadX/common/src/tx_queue_send_notify.o \
./ThreadX/common/src/tx_semaphore_ceiling_put.o \
./ThreadX/common/src/tx_semaphore_cleanup.o \
./ThreadX/common/src/tx_semaphore_create.o \
./ThreadX/common/src/tx_semaphore_delete.o \
./ThreadX/common/src/tx_semaphore_get.o \
./ThreadX/common/src/tx_semaphore_info_get.o \
./ThreadX/common/src/tx_semaphore_initialize.o \
./ThreadX/common/src/tx_semaphore_performance_info_get.o \
./ThreadX/common/src/tx_semaphore_performance_system_info_get.o \
./ThreadX/common/src/tx_semaphore_prioritize.o \
./ThreadX/common/src/tx_semaphore_put.o \
./ThreadX/common/src/tx_semaphore_put_notify.o \
./ThreadX/common/src/tx_thread_create.o \
./ThreadX/common/src/tx_thread_delete.o \
./ThreadX/common/src/tx_thread_entry_exit_notify.o \
./ThreadX/common/src/tx_thread_identify.o \
./ThreadX/common/src/tx_thread_info_get.o \
./ThreadX/common/src/tx_thread_initialize.o \
./ThreadX/common/src/tx_thread_performance_info_get.o \
./ThreadX/common/src/tx_thread_performance_system_info_get.o \
./ThreadX/common/src/tx_thread_preemption_change.o \
./ThreadX/common/src/tx_thread_priority_change.o \
./ThreadX/common/src/tx_thread_relinquish.o \
./ThreadX/common/src/tx_thread_reset.o \
./ThreadX/common/src/tx_thread_resume.o \
./ThreadX/common/src/tx_thread_shell_entry.o \
./ThreadX/common/src/tx_thread_sleep.o \
./ThreadX/common/src/tx_thread_stack_analyze.o \
./ThreadX/common/src/tx_thread_stack_error_handler.o \
./ThreadX/common/src/tx_thread_stack_error_notify.o \
./ThreadX/common/src/tx_thread_suspend.o \
./ThreadX/common/src/tx_thread_system_preempt_check.o \
./ThreadX/common/src/tx_thread_system_resume.o \
./ThreadX/common/src/tx_thread_system_suspend.o \
./ThreadX/common/src/tx_thread_terminate.o \
./ThreadX/common/src/tx_thread_time_slice.o \
./ThreadX/common/src/tx_thread_time_slice_change.o \
./ThreadX/common/src/tx_thread_timeout.o \
./ThreadX/common/src/tx_thread_wait_abort.o \
./ThreadX/common/src/tx_time_get.o \
./ThreadX/common/src/tx_time_set.o \
./ThreadX/common/src/tx_timer_activate.o \
./ThreadX/common/src/tx_timer_change.o \
./ThreadX/common/src/tx_timer_create.o \
./ThreadX/common/src/tx_timer_deactivate.o \
./ThreadX/common/src/tx_timer_delete.o \
./ThreadX/common/src/tx_timer_expiration_process.o \
./ThreadX/common/src/tx_timer_info_get.o \
./ThreadX/common/src/tx_timer_initialize.o \
./ThreadX/common/src/tx_timer_performance_info_get.o \
./ThreadX/common/src/tx_timer_performance_system_info_get.o \
./ThreadX/common/src/tx_timer_system_activate.o \
./ThreadX/common/src/tx_timer_system_deactivate.o \
./ThreadX/common/src/tx_timer_thread_entry.o \
./ThreadX/common/src/tx_trace_buffer_full_notify.o \
./ThreadX/common/src/tx_trace_disable.o \
./ThreadX/common/src/tx_trace_enable.o \
./ThreadX/common/src/tx_trace_event_filter.o \
./ThreadX/common/src/tx_trace_event_unfilter.o \
./ThreadX/common/src/tx_trace_initialize.o \
./ThreadX/common/src/tx_trace_interrupt_control.o \
./ThreadX/common/src/tx_trace_isr_enter_insert.o \
./ThreadX/common/src/tx_trace_isr_exit_insert.o \
./ThreadX/common/src/tx_trace_object_register.o \
./ThreadX/common/src/tx_trace_object_unregister.o \
./ThreadX/common/src/tx_trace_user_event_insert.o \
./ThreadX/common/src/txe_block_allocate.o \
./ThreadX/common/src/txe_block_pool_create.o \
./ThreadX/common/src/txe_block_pool_delete.o \
./ThreadX/common/src/txe_block_pool_info_get.o \
./ThreadX/common/src/txe_block_pool_prioritize.o \
./ThreadX/common/src/txe_block_release.o \
./ThreadX/common/src/txe_byte_allocate.o \
./ThreadX/common/src/txe_byte_pool_create.o \
./ThreadX/common/src/txe_byte_pool_delete.o \
./ThreadX/common/src/txe_byte_pool_info_get.o \
./ThreadX/common/src/txe_byte_pool_prioritize.o \
./ThreadX/common/src/txe_byte_release.o \
./ThreadX/common/src/txe_event_flags_create.o \
./ThreadX/common/src/txe_event_flags_delete.o \
./ThreadX/common/src/txe_event_flags_get.o \
./ThreadX/common/src/txe_event_flags_info_get.o \
./ThreadX/common/src/txe_event_flags_set.o \
./ThreadX/common/src/txe_event_flags_set_notify.o \
./ThreadX/common/src/txe_mutex_create.o \
./ThreadX/common/src/txe_mutex_delete.o \
./ThreadX/common/src/txe_mutex_get.o \
./ThreadX/common/src/txe_mutex_info_get.o \
./ThreadX/common/src/txe_mutex_prioritize.o \
./ThreadX/common/src/txe_mutex_put.o \
./ThreadX/common/src/txe_queue_create.o \
./ThreadX/common/src/txe_queue_delete.o \
./ThreadX/common/src/txe_queue_flush.o \
./ThreadX/common/src/txe_queue_front_send.o \
./ThreadX/common/src/txe_queue_info_get.o \
./ThreadX/common/src/txe_queue_prioritize.o \
./ThreadX/common/src/txe_queue_receive.o \
./ThreadX/common/src/txe_queue_send.o \
./ThreadX/common/src/txe_queue_send_notify.o \
./ThreadX/common/src/txe_semaphore_ceiling_put.o \
./ThreadX/common/src/txe_semaphore_create.o \
./ThreadX/common/src/txe_semaphore_delete.o \
./ThreadX/common/src/txe_semaphore_get.o \
./ThreadX/common/src/txe_semaphore_info_get.o \
./ThreadX/common/src/txe_semaphore_prioritize.o \
./ThreadX/common/src/txe_semaphore_put.o \
./ThreadX/common/src/txe_semaphore_put_notify.o \
./ThreadX/common/src/txe_thread_create.o \
./ThreadX/common/src/txe_thread_delete.o \
./ThreadX/common/src/txe_thread_entry_exit_notify.o \
./ThreadX/common/src/txe_thread_info_get.o \
./ThreadX/common/src/txe_thread_preemption_change.o \
./ThreadX/common/src/txe_thread_priority_change.o \
./ThreadX/common/src/txe_thread_relinquish.o \
./ThreadX/common/src/txe_thread_reset.o \
./ThreadX/common/src/txe_thread_resume.o \
./ThreadX/common/src/txe_thread_suspend.o \
./ThreadX/common/src/txe_thread_terminate.o \
./ThreadX/common/src/txe_thread_time_slice_change.o \
./ThreadX/common/src/txe_thread_wait_abort.o \
./ThreadX/common/src/txe_timer_activate.o \
./ThreadX/common/src/txe_timer_change.o \
./ThreadX/common/src/txe_timer_create.o \
./ThreadX/common/src/txe_timer_deactivate.o \
./ThreadX/common/src/txe_timer_delete.o \
./ThreadX/common/src/txe_timer_info_get.o 

C_DEPS += \
./ThreadX/common/src/tx_block_allocate.d \
./ThreadX/common/src/tx_block_pool_cleanup.d \
./ThreadX/common/src/tx_block_pool_create.d \
./ThreadX/common/src/tx_block_pool_delete.d \
./ThreadX/common/src/tx_block_pool_info_get.d \
./ThreadX/common/src/tx_block_pool_initialize.d \
./ThreadX/common/src/tx_block_pool_performance_info_get.d \
./ThreadX/common/src/tx_block_pool_performance_system_info_get.d \
./ThreadX/common/src/tx_block_pool_prioritize.d \
./ThreadX/common/src/tx_block_release.d \
./ThreadX/common/src/tx_byte_allocate.d \
./ThreadX/common/src/tx_byte_pool_cleanup.d \
./ThreadX/common/src/tx_byte_pool_create.d \
./ThreadX/common/src/tx_byte_pool_delete.d \
./ThreadX/common/src/tx_byte_pool_info_get.d \
./ThreadX/common/src/tx_byte_pool_initialize.d \
./ThreadX/common/src/tx_byte_pool_performance_info_get.d \
./ThreadX/common/src/tx_byte_pool_performance_system_info_get.d \
./ThreadX/common/src/tx_byte_pool_prioritize.d \
./ThreadX/common/src/tx_byte_pool_search.d \
./ThreadX/common/src/tx_byte_release.d \
./ThreadX/common/src/tx_event_flags_cleanup.d \
./ThreadX/common/src/tx_event_flags_create.d \
./ThreadX/common/src/tx_event_flags_delete.d \
./ThreadX/common/src/tx_event_flags_get.d \
./ThreadX/common/src/tx_event_flags_info_get.d \
./ThreadX/common/src/tx_event_flags_initialize.d \
./ThreadX/common/src/tx_event_flags_performance_info_get.d \
./ThreadX/common/src/tx_event_flags_performance_system_info_get.d \
./ThreadX/common/src/tx_event_flags_set.d \
./ThreadX/common/src/tx_event_flags_set_notify.d \
./ThreadX/common/src/tx_initialize_high_level.d \
./ThreadX/common/src/tx_initialize_kernel_enter.d \
./ThreadX/common/src/tx_initialize_kernel_setup.d \
./ThreadX/common/src/tx_misra.d \
./ThreadX/common/src/tx_mutex_cleanup.d \
./ThreadX/common/src/tx_mutex_create.d \
./ThreadX/common/src/tx_mutex_delete.d \
./ThreadX/common/src/tx_mutex_get.d \
./ThreadX/common/src/tx_mutex_info_get.d \
./ThreadX/common/src/tx_mutex_initialize.d \
./ThreadX/common/src/tx_mutex_performance_info_get.d \
./ThreadX/common/src/tx_mutex_performance_system_info_get.d \
./ThreadX/common/src/tx_mutex_prioritize.d \
./ThreadX/common/src/tx_mutex_priority_change.d \
./ThreadX/common/src/tx_mutex_put.d \
./ThreadX/common/src/tx_queue_cleanup.d \
./ThreadX/common/src/tx_queue_create.d \
./ThreadX/common/src/tx_queue_delete.d \
./ThreadX/common/src/tx_queue_flush.d \
./ThreadX/common/src/tx_queue_front_send.d \
./ThreadX/common/src/tx_queue_info_get.d \
./ThreadX/common/src/tx_queue_initialize.d \
./ThreadX/common/src/tx_queue_performance_info_get.d \
./ThreadX/common/src/tx_queue_performance_system_info_get.d \
./ThreadX/common/src/tx_queue_prioritize.d \
./ThreadX/common/src/tx_queue_receive.d \
./ThreadX/common/src/tx_queue_send.d \
./ThreadX/common/src/tx_queue_send_notify.d \
./ThreadX/common/src/tx_semaphore_ceiling_put.d \
./ThreadX/common/src/tx_semaphore_cleanup.d \
./ThreadX/common/src/tx_semaphore_create.d \
./ThreadX/common/src/tx_semaphore_delete.d \
./ThreadX/common/src/tx_semaphore_get.d \
./ThreadX/common/src/tx_semaphore_info_get.d \
./ThreadX/common/src/tx_semaphore_initialize.d \
./ThreadX/common/src/tx_semaphore_performance_info_get.d \
./ThreadX/common/src/tx_semaphore_performance_system_info_get.d \
./ThreadX/common/src/tx_semaphore_prioritize.d \
./ThreadX/common/src/tx_semaphore_put.d \
./ThreadX/common/src/tx_semaphore_put_notify.d \
./ThreadX/common/src/tx_thread_create.d \
./ThreadX/common/src/tx_thread_delete.d \
./ThreadX/common/src/tx_thread_entry_exit_notify.d \
./ThreadX/common/src/tx_thread_identify.d \
./ThreadX/common/src/tx_thread_info_get.d \
./ThreadX/common/src/tx_thread_initialize.d \
./ThreadX/common/src/tx_thread_performance_info_get.d \
./ThreadX/common/src/tx_thread_performance_system_info_get.d \
./ThreadX/common/src/tx_thread_preemption_change.d \
./ThreadX/common/src/tx_thread_priority_change.d \
./ThreadX/common/src/tx_thread_relinquish.d \
./ThreadX/common/src/tx_thread_reset.d \
./ThreadX/common/src/tx_thread_resume.d \
./ThreadX/common/src/tx_thread_shell_entry.d \
./ThreadX/common/src/tx_thread_sleep.d \
./ThreadX/common/src/tx_thread_stack_analyze.d \
./ThreadX/common/src/tx_thread_stack_error_handler.d \
./ThreadX/common/src/tx_thread_stack_error_notify.d \
./ThreadX/common/src/tx_thread_suspend.d \
./ThreadX/common/src/tx_thread_system_preempt_check.d \
./ThreadX/common/src/tx_thread_system_resume.d \
./ThreadX/common/src/tx_thread_system_suspend.d \
./ThreadX/common/src/tx_thread_terminate.d \
./ThreadX/common/src/tx_thread_time_slice.d \
./ThreadX/common/src/tx_thread_time_slice_change.d \
./ThreadX/common/src/tx_thread_timeout.d \
./ThreadX/common/src/tx_thread_wait_abort.d \
./ThreadX/common/src/tx_time_get.d \
./ThreadX/common/src/tx_time_set.d \
./ThreadX/common/src/tx_timer_activate.d \
./ThreadX/common/src/tx_timer_change.d \
./ThreadX/common/src/tx_timer_create.d \
./ThreadX/common/src/tx_timer_deactivate.d \
./ThreadX/common/src/tx_timer_delete.d \
./ThreadX/common/src/tx_timer_expiration_process.d \
./ThreadX/common/src/tx_timer_info_get.d \
./ThreadX/common/src/tx_timer_initialize.d \
./ThreadX/common/src/tx_timer_performance_info_get.d \
./ThreadX/common/src/tx_timer_performance_system_info_get.d \
./ThreadX/common/src/tx_timer_system_activate.d \
./ThreadX/common/src/tx_timer_system_deactivate.d \
./ThreadX/common/src/tx_timer_thread_entry.d \
./ThreadX/common/src/tx_trace_buffer_full_notify.d \
./ThreadX/common/src/tx_trace_disable.d \
./ThreadX/common/src/tx_trace_enable.d \
./ThreadX/common/src/tx_trace_event_filter.d \
./ThreadX/common/src/tx_trace_event_unfilter.d \
./ThreadX/common/src/tx_trace_initialize.d \
./ThreadX/common/src/tx_trace_interrupt_control.d \
./ThreadX/common/src/tx_trace_isr_enter_insert.d \
./ThreadX/common/src/tx_trace_isr_exit_insert.d \
./ThreadX/common/src/tx_trace_object_register.d \
./ThreadX/common/src/tx_trace_object_unregister.d \
./ThreadX/common/src/tx_trace_user_event_insert.d \
./ThreadX/common/src/txe_block_allocate.d \
./ThreadX/common/src/txe_block_pool_create.d \
./ThreadX/common/src/txe_block_pool_delete.d \
./ThreadX/common/src/txe_block_pool_info_get.d \
./ThreadX/common/src/txe_block_pool_prioritize.d \
./ThreadX/common/src/txe_block_release.d \
./ThreadX/common/src/txe_byte_allocate.d \
./ThreadX/common/src/txe_byte_pool_create.d \
./ThreadX/common/src/txe_byte_pool_delete.d \
./ThreadX/common/src/txe_byte_pool_info_get.d \
./ThreadX/common/src/txe_byte_pool_prioritize.d \
./ThreadX/common/src/txe_byte_release.d \
./ThreadX/common/src/txe_event_flags_create.d \
./ThreadX/common/src/txe_event_flags_delete.d \
./ThreadX/common/src/txe_event_flags_get.d \
./ThreadX/common/src/txe_event_flags_info_get.d \
./ThreadX/common/src/txe_event_flags_set.d \
./ThreadX/common/src/txe_event_flags_set_notify.d \
./ThreadX/common/src/txe_mutex_create.d \
./ThreadX/common/src/txe_mutex_delete.d \
./ThreadX/common/src/txe_mutex_get.d \
./ThreadX/common/src/txe_mutex_info_get.d \
./ThreadX/common/src/txe_mutex_prioritize.d \
./ThreadX/common/src/txe_mutex_put.d \
./ThreadX/common/src/txe_queue_create.d \
./ThreadX/common/src/txe_queue_delete.d \
./ThreadX/common/src/txe_queue_flush.d \
./ThreadX/common/src/txe_queue_front_send.d \
./ThreadX/common/src/txe_queue_info_get.d \
./ThreadX/common/src/txe_queue_prioritize.d \
./ThreadX/common/src/txe_queue_receive.d \
./ThreadX/common/src/txe_queue_send.d \
./ThreadX/common/src/txe_queue_send_notify.d \
./ThreadX/common/src/txe_semaphore_ceiling_put.d \
./ThreadX/common/src/txe_semaphore_create.d \
./ThreadX/common/src/txe_semaphore_delete.d \
./ThreadX/common/src/txe_semaphore_get.d \
./ThreadX/common/src/txe_semaphore_info_get.d \
./ThreadX/common/src/txe_semaphore_prioritize.d \
./ThreadX/common/src/txe_semaphore_put.d \
./ThreadX/common/src/txe_semaphore_put_notify.d \
./ThreadX/common/src/txe_thread_create.d \
./ThreadX/common/src/txe_thread_delete.d \
./ThreadX/common/src/txe_thread_entry_exit_notify.d \
./ThreadX/common/src/txe_thread_info_get.d \
./ThreadX/common/src/txe_thread_preemption_change.d \
./ThreadX/common/src/txe_thread_priority_change.d \
./ThreadX/common/src/txe_thread_relinquish.d \
./ThreadX/common/src/txe_thread_reset.d \
./ThreadX/common/src/txe_thread_resume.d \
./ThreadX/common/src/txe_thread_suspend.d \
./ThreadX/common/src/txe_thread_terminate.d \
./ThreadX/common/src/txe_thread_time_slice_change.d \
./ThreadX/common/src/txe_thread_wait_abort.d \
./ThreadX/common/src/txe_timer_activate.d \
./ThreadX/common/src/txe_timer_change.d \
./ThreadX/common/src/txe_timer_create.d \
./ThreadX/common/src/txe_timer_deactivate.d \
./ThreadX/common/src/txe_timer_delete.d \
./ThreadX/common/src/txe_timer_info_get.d 


# Each subdirectory must supply rules for building sources it contributes
ThreadX/common/src/tx_block_allocate.o: ../ThreadX/common/src/tx_block_allocate.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_block_allocate.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_block_pool_cleanup.o: ../ThreadX/common/src/tx_block_pool_cleanup.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_block_pool_cleanup.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_block_pool_create.o: ../ThreadX/common/src/tx_block_pool_create.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_block_pool_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_block_pool_delete.o: ../ThreadX/common/src/tx_block_pool_delete.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_block_pool_delete.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_block_pool_info_get.o: ../ThreadX/common/src/tx_block_pool_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_block_pool_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_block_pool_initialize.o: ../ThreadX/common/src/tx_block_pool_initialize.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_block_pool_initialize.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_block_pool_performance_info_get.o: ../ThreadX/common/src/tx_block_pool_performance_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_block_pool_performance_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_block_pool_performance_system_info_get.o: ../ThreadX/common/src/tx_block_pool_performance_system_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_block_pool_performance_system_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_block_pool_prioritize.o: ../ThreadX/common/src/tx_block_pool_prioritize.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_block_pool_prioritize.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_block_release.o: ../ThreadX/common/src/tx_block_release.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_block_release.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_byte_allocate.o: ../ThreadX/common/src/tx_byte_allocate.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_byte_allocate.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_byte_pool_cleanup.o: ../ThreadX/common/src/tx_byte_pool_cleanup.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_byte_pool_cleanup.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_byte_pool_create.o: ../ThreadX/common/src/tx_byte_pool_create.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_byte_pool_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_byte_pool_delete.o: ../ThreadX/common/src/tx_byte_pool_delete.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_byte_pool_delete.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_byte_pool_info_get.o: ../ThreadX/common/src/tx_byte_pool_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_byte_pool_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_byte_pool_initialize.o: ../ThreadX/common/src/tx_byte_pool_initialize.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_byte_pool_initialize.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_byte_pool_performance_info_get.o: ../ThreadX/common/src/tx_byte_pool_performance_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_byte_pool_performance_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_byte_pool_performance_system_info_get.o: ../ThreadX/common/src/tx_byte_pool_performance_system_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_byte_pool_performance_system_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_byte_pool_prioritize.o: ../ThreadX/common/src/tx_byte_pool_prioritize.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_byte_pool_prioritize.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_byte_pool_search.o: ../ThreadX/common/src/tx_byte_pool_search.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_byte_pool_search.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_byte_release.o: ../ThreadX/common/src/tx_byte_release.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_byte_release.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_event_flags_cleanup.o: ../ThreadX/common/src/tx_event_flags_cleanup.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_event_flags_cleanup.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_event_flags_create.o: ../ThreadX/common/src/tx_event_flags_create.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_event_flags_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_event_flags_delete.o: ../ThreadX/common/src/tx_event_flags_delete.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_event_flags_delete.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_event_flags_get.o: ../ThreadX/common/src/tx_event_flags_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_event_flags_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_event_flags_info_get.o: ../ThreadX/common/src/tx_event_flags_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_event_flags_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_event_flags_initialize.o: ../ThreadX/common/src/tx_event_flags_initialize.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_event_flags_initialize.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_event_flags_performance_info_get.o: ../ThreadX/common/src/tx_event_flags_performance_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_event_flags_performance_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_event_flags_performance_system_info_get.o: ../ThreadX/common/src/tx_event_flags_performance_system_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_event_flags_performance_system_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_event_flags_set.o: ../ThreadX/common/src/tx_event_flags_set.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_event_flags_set.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_event_flags_set_notify.o: ../ThreadX/common/src/tx_event_flags_set_notify.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_event_flags_set_notify.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_initialize_high_level.o: ../ThreadX/common/src/tx_initialize_high_level.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_initialize_high_level.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_initialize_kernel_enter.o: ../ThreadX/common/src/tx_initialize_kernel_enter.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_initialize_kernel_enter.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_initialize_kernel_setup.o: ../ThreadX/common/src/tx_initialize_kernel_setup.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_initialize_kernel_setup.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_misra.o: ../ThreadX/common/src/tx_misra.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_misra.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_mutex_cleanup.o: ../ThreadX/common/src/tx_mutex_cleanup.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_mutex_cleanup.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_mutex_create.o: ../ThreadX/common/src/tx_mutex_create.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_mutex_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_mutex_delete.o: ../ThreadX/common/src/tx_mutex_delete.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_mutex_delete.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_mutex_get.o: ../ThreadX/common/src/tx_mutex_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_mutex_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_mutex_info_get.o: ../ThreadX/common/src/tx_mutex_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_mutex_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_mutex_initialize.o: ../ThreadX/common/src/tx_mutex_initialize.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_mutex_initialize.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_mutex_performance_info_get.o: ../ThreadX/common/src/tx_mutex_performance_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_mutex_performance_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_mutex_performance_system_info_get.o: ../ThreadX/common/src/tx_mutex_performance_system_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_mutex_performance_system_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_mutex_prioritize.o: ../ThreadX/common/src/tx_mutex_prioritize.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_mutex_prioritize.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_mutex_priority_change.o: ../ThreadX/common/src/tx_mutex_priority_change.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_mutex_priority_change.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_mutex_put.o: ../ThreadX/common/src/tx_mutex_put.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_mutex_put.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_queue_cleanup.o: ../ThreadX/common/src/tx_queue_cleanup.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_queue_cleanup.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_queue_create.o: ../ThreadX/common/src/tx_queue_create.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_queue_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_queue_delete.o: ../ThreadX/common/src/tx_queue_delete.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_queue_delete.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_queue_flush.o: ../ThreadX/common/src/tx_queue_flush.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_queue_flush.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_queue_front_send.o: ../ThreadX/common/src/tx_queue_front_send.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_queue_front_send.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_queue_info_get.o: ../ThreadX/common/src/tx_queue_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_queue_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_queue_initialize.o: ../ThreadX/common/src/tx_queue_initialize.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_queue_initialize.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_queue_performance_info_get.o: ../ThreadX/common/src/tx_queue_performance_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_queue_performance_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_queue_performance_system_info_get.o: ../ThreadX/common/src/tx_queue_performance_system_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_queue_performance_system_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_queue_prioritize.o: ../ThreadX/common/src/tx_queue_prioritize.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_queue_prioritize.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_queue_receive.o: ../ThreadX/common/src/tx_queue_receive.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_queue_receive.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_queue_send.o: ../ThreadX/common/src/tx_queue_send.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_queue_send.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_queue_send_notify.o: ../ThreadX/common/src/tx_queue_send_notify.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_queue_send_notify.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_semaphore_ceiling_put.o: ../ThreadX/common/src/tx_semaphore_ceiling_put.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_semaphore_ceiling_put.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_semaphore_cleanup.o: ../ThreadX/common/src/tx_semaphore_cleanup.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_semaphore_cleanup.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_semaphore_create.o: ../ThreadX/common/src/tx_semaphore_create.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_semaphore_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_semaphore_delete.o: ../ThreadX/common/src/tx_semaphore_delete.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_semaphore_delete.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_semaphore_get.o: ../ThreadX/common/src/tx_semaphore_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_semaphore_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_semaphore_info_get.o: ../ThreadX/common/src/tx_semaphore_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_semaphore_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_semaphore_initialize.o: ../ThreadX/common/src/tx_semaphore_initialize.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_semaphore_initialize.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_semaphore_performance_info_get.o: ../ThreadX/common/src/tx_semaphore_performance_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_semaphore_performance_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_semaphore_performance_system_info_get.o: ../ThreadX/common/src/tx_semaphore_performance_system_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_semaphore_performance_system_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_semaphore_prioritize.o: ../ThreadX/common/src/tx_semaphore_prioritize.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_semaphore_prioritize.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_semaphore_put.o: ../ThreadX/common/src/tx_semaphore_put.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_semaphore_put.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_semaphore_put_notify.o: ../ThreadX/common/src/tx_semaphore_put_notify.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_semaphore_put_notify.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_create.o: ../ThreadX/common/src/tx_thread_create.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_delete.o: ../ThreadX/common/src/tx_thread_delete.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_delete.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_entry_exit_notify.o: ../ThreadX/common/src/tx_thread_entry_exit_notify.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_entry_exit_notify.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_identify.o: ../ThreadX/common/src/tx_thread_identify.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_identify.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_info_get.o: ../ThreadX/common/src/tx_thread_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_initialize.o: ../ThreadX/common/src/tx_thread_initialize.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_initialize.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_performance_info_get.o: ../ThreadX/common/src/tx_thread_performance_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_performance_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_performance_system_info_get.o: ../ThreadX/common/src/tx_thread_performance_system_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_performance_system_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_preemption_change.o: ../ThreadX/common/src/tx_thread_preemption_change.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_preemption_change.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_priority_change.o: ../ThreadX/common/src/tx_thread_priority_change.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_priority_change.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_relinquish.o: ../ThreadX/common/src/tx_thread_relinquish.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_relinquish.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_reset.o: ../ThreadX/common/src/tx_thread_reset.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_reset.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_resume.o: ../ThreadX/common/src/tx_thread_resume.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_resume.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_shell_entry.o: ../ThreadX/common/src/tx_thread_shell_entry.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_shell_entry.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_sleep.o: ../ThreadX/common/src/tx_thread_sleep.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_sleep.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_stack_analyze.o: ../ThreadX/common/src/tx_thread_stack_analyze.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_stack_analyze.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_stack_error_handler.o: ../ThreadX/common/src/tx_thread_stack_error_handler.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_stack_error_handler.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_stack_error_notify.o: ../ThreadX/common/src/tx_thread_stack_error_notify.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_stack_error_notify.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_suspend.o: ../ThreadX/common/src/tx_thread_suspend.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_suspend.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_system_preempt_check.o: ../ThreadX/common/src/tx_thread_system_preempt_check.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_system_preempt_check.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_system_resume.o: ../ThreadX/common/src/tx_thread_system_resume.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_system_resume.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_system_suspend.o: ../ThreadX/common/src/tx_thread_system_suspend.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_system_suspend.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_terminate.o: ../ThreadX/common/src/tx_thread_terminate.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_terminate.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_time_slice.o: ../ThreadX/common/src/tx_thread_time_slice.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_time_slice.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_time_slice_change.o: ../ThreadX/common/src/tx_thread_time_slice_change.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_time_slice_change.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_timeout.o: ../ThreadX/common/src/tx_thread_timeout.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_timeout.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_thread_wait_abort.o: ../ThreadX/common/src/tx_thread_wait_abort.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_thread_wait_abort.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_time_get.o: ../ThreadX/common/src/tx_time_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_time_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_time_set.o: ../ThreadX/common/src/tx_time_set.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_time_set.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_timer_activate.o: ../ThreadX/common/src/tx_timer_activate.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_timer_activate.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_timer_change.o: ../ThreadX/common/src/tx_timer_change.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_timer_change.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_timer_create.o: ../ThreadX/common/src/tx_timer_create.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_timer_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_timer_deactivate.o: ../ThreadX/common/src/tx_timer_deactivate.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_timer_deactivate.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_timer_delete.o: ../ThreadX/common/src/tx_timer_delete.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_timer_delete.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_timer_expiration_process.o: ../ThreadX/common/src/tx_timer_expiration_process.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_timer_expiration_process.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_timer_info_get.o: ../ThreadX/common/src/tx_timer_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_timer_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_timer_initialize.o: ../ThreadX/common/src/tx_timer_initialize.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_timer_initialize.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_timer_performance_info_get.o: ../ThreadX/common/src/tx_timer_performance_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_timer_performance_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_timer_performance_system_info_get.o: ../ThreadX/common/src/tx_timer_performance_system_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_timer_performance_system_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_timer_system_activate.o: ../ThreadX/common/src/tx_timer_system_activate.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_timer_system_activate.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_timer_system_deactivate.o: ../ThreadX/common/src/tx_timer_system_deactivate.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_timer_system_deactivate.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_timer_thread_entry.o: ../ThreadX/common/src/tx_timer_thread_entry.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_timer_thread_entry.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_trace_buffer_full_notify.o: ../ThreadX/common/src/tx_trace_buffer_full_notify.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_trace_buffer_full_notify.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_trace_disable.o: ../ThreadX/common/src/tx_trace_disable.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_trace_disable.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_trace_enable.o: ../ThreadX/common/src/tx_trace_enable.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_trace_enable.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_trace_event_filter.o: ../ThreadX/common/src/tx_trace_event_filter.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_trace_event_filter.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_trace_event_unfilter.o: ../ThreadX/common/src/tx_trace_event_unfilter.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_trace_event_unfilter.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_trace_initialize.o: ../ThreadX/common/src/tx_trace_initialize.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_trace_initialize.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_trace_interrupt_control.o: ../ThreadX/common/src/tx_trace_interrupt_control.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_trace_interrupt_control.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_trace_isr_enter_insert.o: ../ThreadX/common/src/tx_trace_isr_enter_insert.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_trace_isr_enter_insert.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_trace_isr_exit_insert.o: ../ThreadX/common/src/tx_trace_isr_exit_insert.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_trace_isr_exit_insert.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_trace_object_register.o: ../ThreadX/common/src/tx_trace_object_register.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_trace_object_register.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_trace_object_unregister.o: ../ThreadX/common/src/tx_trace_object_unregister.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_trace_object_unregister.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/tx_trace_user_event_insert.o: ../ThreadX/common/src/tx_trace_user_event_insert.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/tx_trace_user_event_insert.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_block_allocate.o: ../ThreadX/common/src/txe_block_allocate.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_block_allocate.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_block_pool_create.o: ../ThreadX/common/src/txe_block_pool_create.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_block_pool_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_block_pool_delete.o: ../ThreadX/common/src/txe_block_pool_delete.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_block_pool_delete.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_block_pool_info_get.o: ../ThreadX/common/src/txe_block_pool_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_block_pool_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_block_pool_prioritize.o: ../ThreadX/common/src/txe_block_pool_prioritize.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_block_pool_prioritize.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_block_release.o: ../ThreadX/common/src/txe_block_release.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_block_release.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_byte_allocate.o: ../ThreadX/common/src/txe_byte_allocate.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_byte_allocate.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_byte_pool_create.o: ../ThreadX/common/src/txe_byte_pool_create.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_byte_pool_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_byte_pool_delete.o: ../ThreadX/common/src/txe_byte_pool_delete.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_byte_pool_delete.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_byte_pool_info_get.o: ../ThreadX/common/src/txe_byte_pool_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_byte_pool_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_byte_pool_prioritize.o: ../ThreadX/common/src/txe_byte_pool_prioritize.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_byte_pool_prioritize.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_byte_release.o: ../ThreadX/common/src/txe_byte_release.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_byte_release.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_event_flags_create.o: ../ThreadX/common/src/txe_event_flags_create.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_event_flags_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_event_flags_delete.o: ../ThreadX/common/src/txe_event_flags_delete.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_event_flags_delete.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_event_flags_get.o: ../ThreadX/common/src/txe_event_flags_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_event_flags_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_event_flags_info_get.o: ../ThreadX/common/src/txe_event_flags_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_event_flags_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_event_flags_set.o: ../ThreadX/common/src/txe_event_flags_set.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_event_flags_set.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_event_flags_set_notify.o: ../ThreadX/common/src/txe_event_flags_set_notify.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_event_flags_set_notify.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_mutex_create.o: ../ThreadX/common/src/txe_mutex_create.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_mutex_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_mutex_delete.o: ../ThreadX/common/src/txe_mutex_delete.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_mutex_delete.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_mutex_get.o: ../ThreadX/common/src/txe_mutex_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_mutex_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_mutex_info_get.o: ../ThreadX/common/src/txe_mutex_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_mutex_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_mutex_prioritize.o: ../ThreadX/common/src/txe_mutex_prioritize.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_mutex_prioritize.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_mutex_put.o: ../ThreadX/common/src/txe_mutex_put.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_mutex_put.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_queue_create.o: ../ThreadX/common/src/txe_queue_create.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_queue_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_queue_delete.o: ../ThreadX/common/src/txe_queue_delete.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_queue_delete.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_queue_flush.o: ../ThreadX/common/src/txe_queue_flush.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_queue_flush.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_queue_front_send.o: ../ThreadX/common/src/txe_queue_front_send.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_queue_front_send.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_queue_info_get.o: ../ThreadX/common/src/txe_queue_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_queue_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_queue_prioritize.o: ../ThreadX/common/src/txe_queue_prioritize.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_queue_prioritize.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_queue_receive.o: ../ThreadX/common/src/txe_queue_receive.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_queue_receive.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_queue_send.o: ../ThreadX/common/src/txe_queue_send.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_queue_send.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_queue_send_notify.o: ../ThreadX/common/src/txe_queue_send_notify.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_queue_send_notify.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_semaphore_ceiling_put.o: ../ThreadX/common/src/txe_semaphore_ceiling_put.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_semaphore_ceiling_put.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_semaphore_create.o: ../ThreadX/common/src/txe_semaphore_create.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_semaphore_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_semaphore_delete.o: ../ThreadX/common/src/txe_semaphore_delete.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_semaphore_delete.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_semaphore_get.o: ../ThreadX/common/src/txe_semaphore_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_semaphore_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_semaphore_info_get.o: ../ThreadX/common/src/txe_semaphore_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_semaphore_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_semaphore_prioritize.o: ../ThreadX/common/src/txe_semaphore_prioritize.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_semaphore_prioritize.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_semaphore_put.o: ../ThreadX/common/src/txe_semaphore_put.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_semaphore_put.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_semaphore_put_notify.o: ../ThreadX/common/src/txe_semaphore_put_notify.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_semaphore_put_notify.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_thread_create.o: ../ThreadX/common/src/txe_thread_create.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_thread_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_thread_delete.o: ../ThreadX/common/src/txe_thread_delete.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_thread_delete.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_thread_entry_exit_notify.o: ../ThreadX/common/src/txe_thread_entry_exit_notify.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_thread_entry_exit_notify.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_thread_info_get.o: ../ThreadX/common/src/txe_thread_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_thread_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_thread_preemption_change.o: ../ThreadX/common/src/txe_thread_preemption_change.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_thread_preemption_change.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_thread_priority_change.o: ../ThreadX/common/src/txe_thread_priority_change.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_thread_priority_change.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_thread_relinquish.o: ../ThreadX/common/src/txe_thread_relinquish.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_thread_relinquish.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_thread_reset.o: ../ThreadX/common/src/txe_thread_reset.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_thread_reset.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_thread_resume.o: ../ThreadX/common/src/txe_thread_resume.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_thread_resume.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_thread_suspend.o: ../ThreadX/common/src/txe_thread_suspend.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_thread_suspend.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_thread_terminate.o: ../ThreadX/common/src/txe_thread_terminate.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_thread_terminate.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_thread_time_slice_change.o: ../ThreadX/common/src/txe_thread_time_slice_change.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_thread_time_slice_change.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_thread_wait_abort.o: ../ThreadX/common/src/txe_thread_wait_abort.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_thread_wait_abort.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_timer_activate.o: ../ThreadX/common/src/txe_timer_activate.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_timer_activate.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_timer_change.o: ../ThreadX/common/src/txe_timer_change.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_timer_change.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_timer_create.o: ../ThreadX/common/src/txe_timer_create.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_timer_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_timer_deactivate.o: ../ThreadX/common/src/txe_timer_deactivate.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_timer_deactivate.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_timer_delete.o: ../ThreadX/common/src/txe_timer_delete.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_timer_delete.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/common/src/txe_timer_info_get.o: ../ThreadX/common/src/txe_timer_info_get.c ThreadX/common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/THREADX/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/common/src/txe_timer_info_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

