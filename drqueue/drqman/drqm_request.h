/* $Id: drqm_request.h,v 1.16 2001/10/22 14:16:55 jorge Exp $ */

#ifndef _DRQM_REQUEST_H_
#define _DRQM_REQUEST_H_

#include "drqm_jobs.h"
#include "drqm_computers.h"

/* Requests to MASTER*/
/* Jobs related functions */
void drqm_clean_joblist (struct drqm_jobs_info *info);
void drqm_request_joblist (struct drqm_jobs_info *info);
void drqm_request_job_delete (struct drqm_jobs_info *info);
void drqm_request_job_stop (struct drqm_jobs_info *info);
void drqm_request_job_hstop (struct drqm_jobs_info *info);
void drqm_request_job_continue (struct drqm_jobs_info *info);
void drqm_request_job_frame_waiting (uint32_t jobid,uint32_t frame);
void drqm_request_job_frame_kill (uint32_t jobid,uint32_t frame);
void drqm_request_job_frame_finish (uint32_t jobid,uint32_t frame);
void drqm_request_job_frame_kill_finish (uint32_t jobid,uint32_t frame);
void drqm_request_job_sesupdate (uint32_t jobid,uint32_t frame_start,uint32_t frame_end, uint32_t frame_step);
void drqm_request_job_limits_nmaxcpus_set (uint32_t jobid, uint16_t nmaxcpus);
void drqm_request_job_limits_nmaxcpuscomputer_set (uint32_t jobid, uint16_t nmaxcpuscomputer);

/* Computer related functions */
void drqm_clean_computerlist (struct drqm_computers_info *info);
void drqm_request_computerlist (struct drqm_computers_info *info);

void drqm_request_slave_limits_nmaxcpus_set (char *slave,uint32_t nmaxcpus);
void drqm_request_slave_limits_maxfreeloadcpu_set (char *slave,uint32_t maxfreeloadcpu);
void drqm_request_slave_task_kill (char *slave,uint16_t itask);

#endif /* _DRQM_REQUEST_H_ */
