/* $Id: drqm_request.c,v 1.22 2001/10/22 14:16:54 jorge Exp $ */

#include <stdlib.h>
#include <unistd.h>

#include <libdrqueue.h>

#include "drqm_jobs.h"
#include "drqm_computers.h"
#include "drqm_request.h"

void drqm_request_joblist (struct drqm_jobs_info *info)
{
  /* This function is called non-blocked */
  /* This function is called from inside drqman */
  struct request req;
  int sfd;
  struct job *tjob;	
  int i;

  if ((sfd = connect_to_master ()) == -1) {
    fprintf(stderr,"%s\n",drerrno_str());
    return;
  }

  req.type = R_R_LISTJOBS;

  if (!send_request (sfd,&req,CLIENT))
    goto end;

  if (!recv_request (sfd,&req))
    goto end;

  if (req.type == R_A_LISTJOBS) {
    info->njobs = req.data;
  } else {
    fprintf (stderr,"ERROR: Not appropiate answer to request R_R_LISTJOBS\n");
    goto end;			/* Should I use gotos ? It seems like a reasonable option for this case */
  }

  drqm_clean_joblist (info);
  if ((info->jobs = malloc (sizeof (struct job) * info->njobs)) == NULL) {
    fprintf (stderr,"Not enough memory for job structures\n");
    goto end;
  }
  tjob = info->jobs;
  for (i=0;i<info->njobs;i++) {
    recv_job (sfd,tjob,CLIENT);
    tjob++;
  }

 end:
  close (sfd);
}

void drqm_clean_joblist (struct drqm_jobs_info *info)
{
  if (info->jobs) {
    free (info->jobs);
    info->jobs = NULL;
  }
}

void drqm_request_computerlist (struct drqm_computers_info *info)
{
  /* This function is called non-blocked */
  /* This function is called from inside drqman */
  struct request req;
  int sfd;
  struct computer *tcomputer;	
  int i;

  if ((sfd = connect_to_master ()) == -1) {
    fprintf(stderr,"%s\n",drerrno_str());
    return;
  }

  req.type = R_R_LISTCOMP;

  if (!send_request (sfd,&req,CLIENT)) {
    fprintf(stderr,"%s\n",drerrno_str());
    goto end;
  }
  if (!recv_request (sfd,&req)) {
    fprintf(stderr,"%s\n",drerrno_str());
    goto end;
  }

  if (req.type == R_A_LISTCOMP) {
    info->ncomputers = req.data;
  } else {
    fprintf (stderr,"ERROR: Not appropiate answer to request R_R_TASKFINI\n");
    goto end;			/* Should I use gotos ? It seems like a reasonable option for this case */
  }

  drqm_clean_computerlist (info);
  if ((info->computers = malloc (sizeof (struct computer) * info->ncomputers)) == NULL) {
    fprintf (stderr,"Not enough memory for job structures\n");
    goto end;
  }
  tcomputer = info->computers;
  for (i=0;i<info->ncomputers;i++) {
    computer_init(tcomputer);
    if (!recv_computer (sfd,tcomputer,CLIENT)) {
      fprintf (stderr,"ERROR: Receiving computer structure\n");
      exit (1);
    }
    tcomputer++;
  }

 end:
  close (sfd);
}

void drqm_clean_computerlist (struct drqm_computers_info *info)
{
  if (info->computers) {
    free (info->computers);
    info->computers = NULL;
  }
}

void drqm_request_job_delete (struct drqm_jobs_info *info)
{
  /* This function sends the request to delete the job selected from the queue */
  if (info->njobs) {
    request_job_delete ((uint32_t)info->jobs[info->row].id,CLIENT);
  }
}

void drqm_request_job_stop (struct drqm_jobs_info *info)
{
  /* This function sends the request to stop the job selected from the queue */
  if (info->njobs) {
    request_job_stop ((uint32_t)info->jobs[info->row].id,CLIENT);
  }
}

void drqm_request_job_hstop (struct drqm_jobs_info *info)
{
  /* This function sends the request to hard stop the job selected from the queue */
  if (info->njobs) {
    request_job_hstop ((uint32_t)info->jobs[info->row].id,CLIENT);
  }
}

void drqm_request_job_continue (struct drqm_jobs_info *info)
{
  /* This function sends the request to continue the (stopped) job selected from the queue */
  if (info->njobs) {
    request_job_continue ((uint32_t)info->jobs[info->row].id,CLIENT);
  }
}

void drqm_request_job_frame_waiting (uint32_t jobid,uint32_t frame)
{
  request_job_frame_waiting (jobid,frame,CLIENT);
}

void drqm_request_job_frame_kill (uint32_t jobid,uint32_t frame)
{
  request_job_frame_kill (jobid,frame,CLIENT);
}

void drqm_request_job_frame_finish (uint32_t jobid,uint32_t frame)
{
  request_job_frame_finish (jobid,frame,CLIENT);
}

void drqm_request_job_frame_kill_finish (uint32_t jobid,uint32_t frame)
{
  request_job_frame_kill_finish (jobid,frame,CLIENT);
}

void drqm_request_slave_limits_nmaxcpus_set (char *slave,uint32_t nmaxcpus)
{
  request_slave_limits_nmaxcpus_set (slave,nmaxcpus,CLIENT);
}

void drqm_request_slave_limits_maxfreeloadcpu_set (char *slave,uint32_t maxfreeloadcpu)
{
  request_slave_limits_maxfreeloadcpu_set (slave,maxfreeloadcpu,CLIENT);
}

void drqm_request_slave_task_kill (char *slave,uint16_t itask)
{
  request_slave_killtask (slave,itask,CLIENT);
}

void drqm_request_job_sesupdate (uint32_t jobid,uint32_t frame_start,uint32_t frame_end, uint32_t frame_step)
{
  request_job_sesupdate (jobid,frame_start,frame_end,frame_step,CLIENT);
}

void drqm_request_job_limits_nmaxcpus_set (uint32_t jobid, uint16_t nmaxcpus)
{
  request_job_limits_nmaxcpus_set (jobid,nmaxcpus,CLIENT);
}

void drqm_request_job_limits_nmaxcpuscomputer_set (uint32_t jobid, uint16_t nmaxcpuscomputer)
{
  request_job_limits_nmaxcpuscomputer_set (jobid,nmaxcpuscomputer,CLIENT);
}
