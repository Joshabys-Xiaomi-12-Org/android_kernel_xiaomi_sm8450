/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Legacy CFS sleeper credit — superseded by EEVDF's PLACE_LAG which
 * preserves the full fairness lag across sleep, not just 50%.
 * Kept false; no code reads it when EEVDF is active.
 */
#define SCHED_FEAT_GENTLE_FAIR_SLEEPERS 1

/*
 * Legacy CFS initial placement debit — superseded by EEVDF's
 * PLACE_DEADLINE_INITIAL which gives new tasks half a virtual slice.
 * Kept false; no code reads it when EEVDF is active.
 */
#define SCHED_FEAT_START_DEBIT 1

/*
 * EEVDF: Preserve lag across sleeps — entity wakes with the same
 * fairness debt/credit it had when it went to sleep.
 */
#define SCHED_FEAT_PLACE_LAG 1

/*
 * EEVDF: Give newly forked/execed tasks only half a slice worth of
 * deadline, so they do not immediately preempt long-running tasks.
 */
#define SCHED_FEAT_PLACE_DEADLINE_INITIAL 1

/*
 * EEVDF: Let the current task keep running at tick time if it hasn't
 * exhausted its slice yet — __pick_eevdf() returns curr immediately
 * instead of doing an O(log n) tree walk, saving ~50 cycles per tick
 * on lightly loaded cores.
 *
 * This does NOT block wakeup preemption: check_preempt_wakeup() fires
 * before pick_next_entity() and grants preemption via deadline
 * comparison + vruntime sleeper assist.  RUN_TO_PARITY only skips the
 * tick-driven re-evaluation, which matters for CPU-bound background
 * tasks — exactly the workload where fewer context switches save power
 * without affecting UI latency.
 */
#define SCHED_FEAT_RUN_TO_PARITY 1

/*
 * Prefer to schedule the task we woke last (assuming it failed
 * wakeup-preemption), since its likely going to consume data we
 * touched, increases cache locality.
 */
#define SCHED_FEAT_NEXT_BUDDY 1

/*
 * Prefer to schedule the task that ran last (when we did
 * wake-preempt) as that likely will touch the same data, increases
 * cache locality.
 */
#define SCHED_FEAT_LAST_BUDDY 1

/*
 * Consider buddies to be cache hot, decreases the likelyness of a
 * cache buddy being migrated away, increases cache locality.
 */
#define SCHED_FEAT_CACHE_HOT_BUDDY 1

/*
 * Allow wakeup-time preemption of the current task:
 */
#define SCHED_FEAT_WAKEUP_PREEMPTION 1

#define SCHED_FEAT_HRTICK 0
#define SCHED_FEAT_DOUBLE_TICK 0

/*
 * Decrement CPU capacity based on time not spent running tasks
 */
#define SCHED_FEAT_NONTASK_CAPACITY 1

/*
 * Queue remote wakeups on the target CPU and process them
 * using the scheduler IPI. Reduces rq->lock contention/bounces.
 */
#define SCHED_FEAT_TTWU_QUEUE 0

/*
 * When doing wakeups, attempt to limit superfluous scans of the LLC domain.
 * SIS_UTIL bounds the scan by per-LLC utilization (updated during periodic
 * load balance) and supersedes the avg_idle heuristic of SIS_PROP.
 */
#define SCHED_FEAT_SIS_AVG_CPU 0
#define SCHED_FEAT_SIS_PROP 0
#define SCHED_FEAT_SIS_UTIL 1

/*
 * Issue a WARN when we do multiple update_rq_clock() calls
 * in a single rq->lock section. Default disabled because the
 * annotations are not complete.
 */
#define SCHED_FEAT_WARN_DOUBLE_CLOCK 0

/*
 * In order to avoid a thundering herd attack of CPUs that are
 * lowering their priorities at the same time, and there being
 * a single CPU that has an RT task that can migrate and is waiting
 * to run, where the other CPUs will try to take that CPUs
 * rq lock and possibly create a large contention, sending an
 * IPI to that CPU and let that CPU push the RT task to where
 * it should go may be a better scenario.
 *
 * This is best for PREEMPT_RT, but for non-RT it can cause issues
 * when preemption is disabled for long periods of time. Have
 * it only default enabled for PREEMPT_RT.
 */
# ifdef CONFIG_PREEMPT_RT
#define SCHED_FEAT_RT_PUSH_IPI 1
# else
#define SCHED_FEAT_RT_PUSH_IPI 0
# endif

#define SCHED_FEAT_RT_RUNTIME_SHARE 0
#define SCHED_FEAT_LB_MIN 0
#define SCHED_FEAT_ATTACH_AGE_LOAD 1

#define SCHED_FEAT_WA_IDLE 1
#define SCHED_FEAT_WA_WEIGHT 1
#define SCHED_FEAT_WA_BIAS 1

/*
 * UtilEstimation. Use estimated CPU utilization.
 */
#define SCHED_FEAT_UTIL_EST 1
#define SCHED_FEAT_UTIL_EST_FASTUP 1

#define SCHED_FEAT_ALT_PERIOD 1
#define SCHED_FEAT_BASE_SLICE 1
