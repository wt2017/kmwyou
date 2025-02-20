#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/ptp_clock_kernel.h>

#define PTP_CLOCK_NAME "wyou_ptp_clock"

static int
wyou_ptp_settime64(struct ptp_clock_info *info, const struct timespec64 *ts)
{
    pr_info("wyou_ptp_settime64 called\n");
    return 0;
}

static int
wyou_ptp_gettimex64(struct ptp_clock_info *info, struct timespec64 *ts,
		   struct ptp_system_timestamp *sts)
{
	pr_info("wyou_ptp_gettimex64 called\n");
	return 0;
}

static int 
wyou_ptp_adjtime(struct ptp_clock_info *info, s64 delta)
{
	pr_info("wyou_ptp_adjtime called\n");
	return 0;
}

static int 
wyou_ptp_adjfine(struct ptp_clock_info *info, long scaled_ppm)
{
	pr_info("wyou_ptp_adjfine called\n");
	return 0;
}

static struct ptp_clock_info wyou_ptp_clock_info = {
    .owner      = THIS_MODULE,
    .name       = PTP_CLOCK_NAME,
    .max_adj    = 1000000,
    .n_alarm    = 0,
    .n_ext_ts   = 0,
    .n_per_out  = 0,
    .n_pins     = 0,
    .pps        = 0,
    .gettimex64  = wyou_ptp_gettimex64,
    .settime64  = wyou_ptp_settime64,
    .adjtime    = wyou_ptp_adjtime,
    .adjfine    = wyou_ptp_adjfine,
};

static struct ptp_clock *my_ptp_clock;

static int __init wyou_ptp_clock_init(void) {
    my_ptp_clock = ptp_clock_register(&wyou_ptp_clock_info, NULL);
    if (IS_ERR(my_ptp_clock)) {
        pr_err("Failed to register PTP clock\n");
        return PTR_ERR(my_ptp_clock);
    }

    pr_info("Wyou PTP clock registered successfully\n");
    return 0;
}

static void __exit wyou_ptp_clock_exit(void) {
    if (my_ptp_clock) {
        ptp_clock_unregister(my_ptp_clock);
        pr_info("Wyou PTP clock unregistered\n");
    }
}

module_init(wyou_ptp_clock_init);
module_exit(wyou_ptp_clock_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("You Wentao");
MODULE_DESCRIPTION("A Wyou PTP clock driver");
MODULE_VERSION("1.0");
