#define DEBUG

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/module.h>
#include <linux/virtio.h>

#include "virtio_dri.h"

static int virtdri_validate(struct virtio_device *vdev)
{
	pr_info(">>> %s\n", __func__);
	return 0;
}

static int virtdri_probe(struct virtio_device *vdev)
{
	pr_info(">>> %s\n", __func__);
	return 0;
}

static void virtdri_remove(struct virtio_device *vdev)
{
	pr_info(">>> %s\n", __func__);
	return;
}

static void virtdri_changed(struct virtio_device *vdev)
{
	pr_info(">>> %s\n", __func__);
	return;
}

static struct virtio_device_id id_table[] = {
	{ VIRTIO_ID_DRI, VIRTIO_DEV_ANY_ID },
	{ 0 },
};

static unsigned int features[] = {
};

static struct virtio_driver virtio_dri_driver = {
	.feature_table = features,
	.feature_table_size = ARRAY_SIZE(features),
	.driver = {
		.name = KBUILD_MODNAME,
		.owner = THIS_MODULE,
	},
	.id_table = id_table,
	.validate = virtdri_validate,
	.probe = virtdri_probe,
	.remove = virtdri_remove,
	.config_changed = virtdri_changed,
};

module_virtio_driver(virtio_dri_driver);
MODULE_DEVICE_TABLE(virtio, id_table);
MODULE_DESCRIPTION("Virtio dri driver");
MODULE_LICENSE("GPL");
